// playground.js
import { transpileWeb } from './web-t.js';

const editor = document.getElementById('editor');
const runButton = document.getElementById('runButton');
const consoleDiv = document.getElementById('console');

function clearConsole() {
    consoleDiv.innerHTML = '';
}

function printConsole(msg, type="log") {
    const pre = document.createElement('pre');
    pre.textContent = msg;
    pre.className = type;
    consoleDiv.appendChild(pre);
    consoleDiv.scrollTop = consoleDiv.scrollHeight;
}

runButton.addEventListener('click', () => {
    clearConsole();
    const codeMS = editor.value;
    let js;
    
    try {
        js = transpileWeb(codeMS, "<playground>");
        // No imprimimos el JS
    } catch(e) {
        printConsole(e.message, "error");
        return;
    }

    try {
        const sandboxConsole = {
            log: (...args) => printConsole(args.join(' '), "log"),
            error: (...args) => printConsole(args.join(' '), "error"),
            warn: (...args) => printConsole(args.join(' '), "warn"),
        };
        const fn = new Function("console", js);
        fn(sandboxConsole);
    } catch(e) {
        printConsole(e.message, "error");
    }
});

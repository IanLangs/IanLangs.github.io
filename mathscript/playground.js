// playground.js
import { transpileWeb } from './web-transpile.js';

const editor = document.getElementById('editor');
const runButton = document.getElementById('runButton');
const consoleDiv = document.getElementById('console');

function printConsole(msg, type="log") {
    const p = document.createElement('pre');
    p.textContent = msg;
    p.className = type;
    consoleDiv.appendChild(p);
}

function clearConsole() {
    consoleDiv.innerHTML = '';
}

runButton.addEventListener('click', () => {
    clearConsole();
    const codeMS = editor.value;
    let js;
    try {
        js = transpileWeb(codeMS, "<playground>");
        printConsole(js, "transpiled");
    } catch(e) {
        printConsole(e.message, "error");
        return;
    }

    try {
        const _console = console;
        const sandbox = {
            console: {
                log: (...args) => printConsole(args.join(' '), "log"),
                error: (...args) => printConsole(args.join(' '), "error"),
                warn: (...args) => printConsole(args.join(' '), "warn")
            }
        };
        const fn = new Function("console", js);
        fn(sandbox.console);
    } catch(e) {
        printConsole(e.message, "error");
    }
});

export const Consts = [
    [/::\s*[^\s\(\)]*/g, ""],
    [/mut\s+([a-zA-Z_]\w*)\s*=\s*(.+)/g, "let $1= (()=>{let v=$2; return {get:()=>v,set:n=>v=n}})()"],
    [/immut\s+([a-zA-Z_]\w*)/g, "delete $1.set"],
    [/using\(/g, "require("],
    [/fn/g, "function"],
];

export function transpile(code, ...consts) {
    for (let [i,j] of consts) {
        code = code.replace(i,j);
    }
    return code;
}

const editor = document.getElementById('editor');
const consoleDiv = document.getElementById('console');
const runButton = document.getElementById('runButton');

const originalLog = console.log;
console.log = (...args) => {
    originalLog(...args);
    const line = document.createElement('pre');
    const code = document.createElement('code');
    code.className = 'language-bash';
    code.textContent = args.join(' ');
    line.appendChild(code);
    consoleDiv.appendChild(line);
    Prism.highlightElement(code);
    consoleDiv.scrollTop = consoleDiv.scrollHeight;
};

runButton.addEventListener('click', () => {
    consoleDiv.textContent = '';
    try {
        const code = transpile(editor.value, ...(Consts));
        new Function(`(function(){${code}})()`)();
    } catch(e) {
        const line = document.createElement('pre');
        const code = document.createElement('code');
        code.className = 'language-bash';
        code.textContent = 'Error: ' + e.message;
        line.appendChild(code);
        consoleDiv.appendChild(line);
        Prism.highlightElement(code);
    }
});

const change = {
  "class":(name, tag, num)=>{
    (document.getElementsByTagName(tag)[num]).className = name
  }
}

function change(type, name, tag, num) {
  change[type](name, tag, num)
}

const change = {
  "class":(name, tag, num)=>{
    (document.getElementsByTagName(tag)[num]).className = name
  }
}

function change(type, name, tag, num) {
  change[type](name, tag, num)
}


// Activa el enlace del menú según lo que clickees
document.querySelectorAll('.nav-link').forEach(link => {
  link.addEventListener('click', () => {
    document.querySelectorAll('.nav-link').forEach(l => l.classList.remove('active'));
    link.classList.add('active');
  });
});

// Scroll suave a la sección deseada
function scrollToSection(id) {
  const el = document.getElementById(id);
  if (el) el.scrollIntoView({ behavior: 'smooth' });
}

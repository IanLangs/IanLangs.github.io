const params = new URLSearchParams(location.search);
const name = params.get("name");

const projects = {
  repy: {
    rname:"RePy",
    title: "Descargar RePy",
    desc: "Puedes descargar la última versión de RePy desde el siguiente enlace:",
    downloads: [
      { label: "Linux", file: "./RePylinux.zip" },
      { label: "Windows", file: "./RePywin.zip" }
    ],
    github: "https://www.github.com/IanLangs/RePy"
  },

  pmake: {
    rname:"PMAKE",
    title: "Descargar PMAKE",
    desc: "Puedes descargar la última versión de PMAKE desde el siguiente enlace:",
    downloads: [
      { label: "Linux", file: "./PMAKElinux.zip" }
    ],
    github: "https://www.github.com/IanLangs/PMAKE"
  }
};

const app = document.getElementById("app");
const footer = document.getElementById("footer");

const p = projects[name];

if (!p) {
  document.title = "Proyecto no encontrado";
  app.innerHTML = "<h1>Proyecto no encontrado</h1>";
} else {
  document.title = `descarga-${p.rname}`;

  app.innerHTML = `
    <h1 class="Destacado">${p.title}</h1>
    <p>${p.desc}</p>

    ${p.downloads
      .map(d => `<a href="${d.file}" download>Descargar ${p.rname} ${d.label}</a><br>`)
      .join("")}

    <br><br><br>
    <a href="./index.html">Pagina principal</a>
  `;

  footer.innerHTML = `
    <ul>
      <li><a href="https://www.github.com/IanLangs">github de IanLangs</a></li>
      <li><a href="https://IanLangs.github.io">IanLangs.github.io</a></li>
      <li><a href="${p.github}">${p.rname} github</a></li>
      <li>feedback en el repo de github</li>
    </ul>
  `;
}

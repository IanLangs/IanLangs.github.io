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
    github: "https://www.github.com/IanLangs/RePy",
    haveGithub: true
  },

  pmake: {
    rname:"PMAKE",
    title: "Descargar PMAKE",
    desc: "Puedes descargar la última versión de PMAKE desde el siguiente enlace:",
    downloads: [
      { label: "Linux", file: "./PMAKElinux.zip" }
    ],
    github: "https://www.github.com/IanLangs/PMAKE",
    haveGithub: true
  },

  ipm: {
    rname:"ipm",
    title:"Descargar ipm",
    desc:"Puedes descargar la última versión de ipm desde el siguiente enlace:",
    downloads: [
      { label: "Linux", file: "./ipm.deb" }
    ],
    github:"https://github.com/IanLangs/ipm",
    haveGithub: true
  },

  cink: {
    rname:"c-ink",
    title:"Descargar c-ink",
    desc:"Puedes descargar la última versión de c-ink desde el siguiente enlace:",
    downloads: [
      { label: "Linux", file: "./cink.deb" }
    ],
    github:"https://github.com/IanLangs/c-ink",
    haveGithub: true
  },

  icc: {
    rname:"icc",
    title:"Descargar icc",
    desc:"Puedes descargar la última versión de icc desde el siguiente enlace:",
    downloads: [
      {
        label: "Linux (deb)",
        file: "./icc.deb"
      },
      {
        label: "Linux (rpm)",
        file: "./icc.rpm"
      },
      {
        label: "Windows (msi)",
        file: "./icc.msi"
      }
    ],
    github:"No have a only repo"
  },
};

const app = document.querySelector("#app");
const footer = document.querySelector("#footer");

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
      <li>${p.haveGithub == true ? `<a href="${p.github}">${p.rname}` : "no have"} github</a></li>
      <li>feedback en el repo de github</li>
    </ul>
  `;
}

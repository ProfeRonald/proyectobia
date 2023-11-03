//asignar un nombre y version al cache
var month = new Date();
const CACHE_NAME = "BIApwa" + month.getMonth(),
  urlsToCache = [
    "",
  ];

//durante la fase de instalacion, generalmente se almacena en cache los activos estaticos
self.addEventListener("install", (e) => {
  e.waitUntil(
    caches
      .open(CACHE_NAME)
      .then((cache) => {
        return cache.addAll(urlsToCache).then(() => self.skipWaiting());
      })
      .catch((err) => console.log("NO cache", err))
  );
});

//una vez que se instala el SW, se activa y busca los recursos para hacer que funcione sin conexion
self.addEventListener("activate", (e) => {
  const cacheWhitelist = [CACHE_NAME];

  e.waitUntil(
    caches
      .keys()
      .then((cacheNames) => {
        return Promise.all(
          cacheNames.map((cacheName) => {
            //Eliminamos lo que ya no se necesita en cache
            if (cacheWhitelist.indexOf(cacheName) === -1) {
              return caches.delete(cacheName);
            }
          })
        );
      })
      // Le indica al SW activar el cache actual
      .then(() => self.clients.claim())
  );
});

//cuando el navegador recupera una url
self.addEventListener("fetch", (e) => {
  //Responder ya sea con el objeto en cache o continuar y buscar la url real
  e.respondWith(
    caches.match(e.request).then((res) => {
      if (res) {
        //recuperar del cache
        return res;
      }
      //recuperar de la peticion a la url
      return fetch(e.request);
    })
  );
});

//BORRAR CACHE
//caches.delete('BIApwa');

//BORRAR TODAS LAS CACHE
/*caches.keys().then(function(names) {
    for (let name of names)
        caches.delete(name);
});*/

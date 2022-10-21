# Sistemas Computacionales

---

## Tarea Extraclase

### Instalar el servicio

Una vez que nos encontremos en la carpeta raiz del proyecto:

- Editamos el archivo `file.conf` introduciendo los _path_ de los archivos que deseamos observar sus cambios

- Ejecutar

```shell
 sudo ./install
```

- Luego ya estará instalado el servicio que expondremos mediante el comando `filewatcher`

### Modo de uso

```shell
sudo filewatcher {start|stop|status|log}
```

### Detalles

Tendremos corriendo un timer `file_watcher.timer` el cual activará cada minuto al servicio `file_watcher.service`, observando los archivos listados en `file.conf`. La configuración por defecto tomará el directorio `./test/` y lo copiará durante la instalación a `/shared/` para más detalles de configuración referirse al archivo `install` ya que es el encargado de preparar todo el entorno.

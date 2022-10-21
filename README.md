# Sistemas Computacionales

---

## Tarea Extraclase

### Watcher

Para la creación del archivo ejecutable `my_watcher` ejecute el siguiente comando en el directorio donde se encuentre el archivo `Makefile`:

```shell
make
```

Esto generará las biblioteca estática `libfile_log.a` así como el fichero objeto `file_log.o`.

En caso de solo necesitar el fichero ejecutable introduzca el siguiente comando:

```shell
make clean
```

> El comando anterior elimina los ficheros objeto así como las bibliotecas necesarias para el proceso de compilación del ejecutable `my_watcher`

### Instalar el servicio

Una vez generado el archivo ejecutable es momento de instalar el servicio deseado.
Para ello realice los siguientes pasos:

- Pararse dentro del directorio actual y editar el archivo `file.conf` introduciendo los _path_ de los archivos que deseamos observar sus cambios

- Ejecutar

```shell
 sudo ./install
```

- Luego ya estará instalado el servicio que expondremos mediante el comando `filewatcher`

```shell
sudo filewatcher
```

El comando le mostrará las opciones ofrecidas.

### Detalles

Tendremos corriendo un timer `file_watcher.timer` el cual activará cada minuto al servicio `file_watcher.service`, observando los archivos en `./test/`, directorio que se copiará durante la instalación a `/shared/` para más detalles de configuración referirse al archivo `install` ya que es el encargado de preparar todo el entorno.

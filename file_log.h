
#ifndef _FILE_LOG
#define _FILE_LOG
#define MAXLEN 255

#define CONF_FILE_PATH "/etc/sec-info/file.conf"

#define _USE_32BIT_TIME_T 1
#define SUFIX_FOR_TEMP_FILES ".watcher"

// Determina la cantidad de archivos a verificar
int process_files(char *);

// Obtiene la fecha de la última modificación de un archivo
time_t fmod_status(char *);

// Obtiene la fecha de la última modificación de un archivo en la ultima vez que se chequeo
time_t fmod_last_tick_status(char *);

// Dado un archivo salva la fecha chequeada en los archivos temporales
void save_fmod_status(char *);

// Obtiene el id del usuario que ha modificado el archivo
uid_t user_status(char *);

// Verifica si alguno de los archivos definidos han sido modificados
void check_if_file_change(char *);

#endif

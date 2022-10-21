#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <systemd/sd-journal.h>

#include <file_log.h>

#define _USE_32BIT_TIME_T 1
#define SUFIX_FOR_TEMP_FILES "watcher"

char *ltrim(char *s)
{
    while (isspace(*s))
        s++;
    return s;
}

char *rtrim(char *s)
{
    char *back = s + strlen(s);
    while (isspace(*--back))
        ;
    *(back + 1) = '\0';
    return s;
}

char *trim(char *s)
{
    return rtrim(ltrim(s));
}

// Determina la cantidad de archivos a verificar
int process_files(char *files_list)
{
    FILE *stream;
    int count = 0;
    char *file_name = NULL;
    size_t size = 0;
    ssize_t p_read;

    stream = fopen(files_list, "r");
    if (stream == NULL)
    {

        perror("Error al abrir el archivo de configuracion");
        exit(EXIT_FAILURE);
    }

    // Observa si se han realizado cambios desde la ultima vez
    while ((p_read = getline(&file_name, &size, stream)) != -1)
    {
        file_name = trim(file_name);
        check_if_file_change(file_name);
        if (p_read != 0)
            ++count;
    }

    free(file_name);
    fclose(stream);

    return count;
}

// Obtiene la fecha de la última modificación de un archivo
time_t fmod_status(char *file_name)
{
    struct stat sb;
    if (stat(file_name, &sb) == -1)
    {
        sd_journal_print(LOG_ERR, strcat(file_name, " do not exists"));
        perror("Fail while getting file info [Time of last data modification actual file]");
        exit(EXIT_FAILURE);
    }

    return sb.st_mtime;
}

// Obtiene la fecha de la última modificación de un archivo en la ultima vez que se chequeo
time_t fmod_last_tick_status(char *file_name)
{
    struct stat sb;
    char t_file_name[120] = "";
    strcpy(t_file_name, file_name);
    strcat(t_file_name, SUFIX_FOR_TEMP_FILES);

    if (stat(t_file_name, &sb) == -1)
    {
        sd_journal_print(LOG_NOTICE, "File %s was registered has log watcher \n", t_file_name);
        time_t daemon_time = time(NULL);
        return daemon_time;
    }

    return sb.st_mtime;
}

// Dado un archivo salva la fecha chequeada en los archivos temporales
void save_fmod_status(char *file_name)
{
    char data[20] = "Se ha salvado";
    FILE *fPtr;

    char t_file_name[120] = "";
    strcpy(t_file_name, file_name);
    strcat(t_file_name, SUFIX_FOR_TEMP_FILES);

    fPtr = fopen(t_file_name, "w+");

    if (fPtr == NULL)
    {
        /* File not created hence exit */
        sd_journal_print(LOG_ERR, "Se ha fallado al crear el archivo temporal %s.\n", t_file_name);
        exit(EXIT_FAILURE);
    }

    /* Write data to file */
    fputs(data, fPtr);

    /* Close file to save file data */
    fclose(fPtr);
}

// Obtiene el id del usuario que ha modificado el archivo
uid_t user_status(char *file_name)
{
    struct stat sb;
    if (stat(file_name, &sb) == -1)
    {
        perror("Fail while getting file info [User ID of file]");
        exit(EXIT_FAILURE);
    }

    return sb.st_uid;
}

// Verifica si alguno de los archivos definidos han sido modificados
void check_if_file_change(char *file_name)
{
    double diff = difftime(fmod_last_tick_status(file_name), fmod_status(file_name));
    if (diff < 0)
    {
        sd_journal_print(LOG_NOTICE, "File %s was modified \n", file_name);
        sd_journal_print(LOG_NOTICE, "User ID: %d \n", user_status(file_name));
        save_fmod_status(file_name);
    }
}

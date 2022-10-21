#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <systemd/sd-journal.h>
#include <unistd.h>

#include <file_log.h>

#define _USE_32BIT_TIME_T 1

int main()
{
    char *files_list = "/etc/sec-info/file.conf";
    process_files(files_list);
    fflush(NULL);
}

#include <fcntl.h>
#include <sys/stat.h>

int create256dir(char *prefix) {
    char buf[1024];
    int j;

    for (j = 0; j < 256; j++) {
        snprintf(buf,sizeof(buf),"%s%02x",prefix,j);
        if (mkdir(buf,0755) == -1) {
            redisLog(REDIS_WARNING,"Error creating dir %s for diskstore: %s",
                buf,strerror(errno));
            return REDIS_ERR;
        }
    }
    return REDIS_OK;
}

int dsOpen(void) {
    struct stat sb;
    int retval, j;
    char *path = server.ds_path;
    char buf[1024];

    if ((retval = stat(path,&sb) == -1) && errno != ENOENT) {
        redisLog(REDIS_WARNING, "Error opening disk store at %s: %s",

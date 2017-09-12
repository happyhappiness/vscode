#include <fcntl.h>
#include <sys/stat.h>

int dsOpen(void) {
    struct stat sb;
    int retval;
    char *path = server.ds_path;

    if ((retval = stat(path,&sb) == -1) && errno != ENOENT) {
        redisLog(REDIS_WARNING, "Error opening disk store at %s: %s",

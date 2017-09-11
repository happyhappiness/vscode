#define ERROR(...) { \
    char __buf[1024]; \
    sprintf(__buf, __VA_ARGS__); \
    sprintf(error, "0x%08lx: %s", epos, __buf); \
}

static char error[1024];
static long epos;

int consumeNewline(char *buf) {
    if (strncmp(buf,"\r\n",2) != 0) {

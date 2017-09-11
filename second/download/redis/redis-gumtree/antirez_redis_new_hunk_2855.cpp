#define ERROR(...) { \
    char __buf[1024]; \
    sprintf(__buf, __VA_ARGS__); \
    sprintf(error, "0x%16llx: %s", (long long)epos, __buf); \
}

static char error[1024];
static off_t epos;

int consumeNewline(char *buf) {
    if (strncmp(buf,"\r\n",2) != 0) {

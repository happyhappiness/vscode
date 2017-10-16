  char *libcurl; /* output libcurl code to this file name */
  bool raw;
  bool post301;
  bool nokeepalive; /* for keepalive needs */
  long alivetime;

  struct OutStruct *outs;
};

#define WARN_PREFIX "Warning: "
#define WARN_TEXTWIDTH (79 - (int)strlen(WARN_PREFIX))
/* produce this text message to the user unless mute was selected */
static void warnf(struct Configurable *config, const char *fmt, ...)
{
  if(!(config->conf & CONF_MUTE)) {
    va_list ap;
    int len;
    char *ptr;
    char print_buffer[256];

    va_start(ap, fmt);


void plugin_log (int level, const char *format, ...);
#define ERROR(...)   plugin_log (LOG_ERR,     __VA_ARGS__)
#define WARNING(...) plugin_log (LOG_WARNING, __VA_ARGS__)
#define NOTICE(...)  plugin_log (LOG_NOTICE,  __VA_ARGS__)
#define INFO(...)    plugin_log (LOG_INFO,    __VA_ARGS__)
#define DEBUG(...)   plugin_log (LOG_DEBUG,   __VA_ARGS__)

/* TODO: Move plugin_{complain,relief} into `utils_complain.[ch]'. -octo */
void plugin_complain (int level, complain_t *c, const char *format, ...);
void plugin_relief (int level, complain_t *c, const char *format, ...);

const data_set_t *plugin_get_ds (const char *name);

 *              function.
 */
int plugin_dispatch_values (const char *name, value_list_t *vl);

int plugin_dispatch_notification (const notification_t *notif);

void plugin_log (int level, const char *format, ...);
#define ERROR(...)   plugin_log (LOG_ERR,     __VA_ARGS__)
#define WARNING(...) plugin_log (LOG_WARNING, __VA_ARGS__)
#define NOTICE(...)  plugin_log (LOG_NOTICE,  __VA_ARGS__)
#define INFO(...)    plugin_log (LOG_INFO,    __VA_ARGS__)
#if COLLECT_DEBUG
# define DEBUG(...)  plugin_log (LOG_DEBUG,   __VA_ARGS__)

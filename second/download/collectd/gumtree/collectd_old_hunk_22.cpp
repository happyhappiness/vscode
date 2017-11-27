 *  If `dir' is NULL the compiled in default `PLUGINDIR' is used.
 */
void plugin_set_dir (const char *dir);

/*
 * NAME
 *  plugin_count
 *
 * DESCRIPTION
 *  trivial
 *
 * RETURN VALUE
 *  The number of currently loaded plugins
 */
int plugin_count (void);

/*
 * NAME
 *  plugin_exists
 *
 * DESCRIPTION
 *  trivial
 *
 * ARGUMENTS
 *  `type'      Name of the plugin.
 *
 * RETURN VALUE
 *  Returns non-zero if a plugin with the name $type is found and zero
 *  otherwise.
 */
int plugin_exists (char *type);

/*
 * NAME
 *  plugin_load
 *
 * DESCRIPTION
 *  Searches the current `plugindir' (see `plugin_set_dir') for the plugin
 *  named $type and loads it. Afterwards the plugin's `module_register'
 *  function is called, which then calls `plugin_register' to register callback
 *  functions.
 *
 * ARGUMENTS
 *  `type'      Name of the plugin to load.
 *
 * RETURN VALUE
 *  Returns zero upon success, a value greater than zero if no plugin was found
 *  and a value below zero if an error occurs.
 *
 * NOTES
 *  No attempt is made to re-load an already loaded module.
 */
int  plugin_load (const char *type);

int  plugin_load_all (char *dir);
void plugin_init_all (void);
void plugin_read_all (const int *loop);

void plugin_shutdown_all (void);

void plugin_register (char *type,
		void (*init) (void),
		void (*read) (void),
		void (*write) (char *, char *, char *));

int plugin_register_shutdown (char *, void (*) (void));

/*
 * NAME
 *  plugin_write
 *
 * DESCRIPTION
 *  Searches the plugin for `type' in the plugin-list. If found, and a `write'
 *  function is registered, it's called. If either the plugin is not found or
 *  the plugin doesn't provide a `write' function this function will return
 *  without further notice.
 *
 * ARGUMENTS
 *  `host'      Host(name) from which the data originates.
 *  `type'      Name of the plugin.
 *  `inst'      Instance (passed to the plugin's `write' function.
 *  `val'       Values for the RRD files. Also passed to the plugin.
 */
void plugin_write    (char *host, char *type, char *inst, char *val);

void plugin_submit   (char *type, char *inst, char *val);


void plugin_complain (int level, complain_t *c, const char *format, ...);
void plugin_relief (int level, complain_t *c, const char *format, ...);

#endif /* PLUGIN_H */

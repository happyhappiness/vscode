 			ret = (*cf_cb->callback) (key, value);
 			break;
 		}
 	}
 
 	if (i >= cf_cb->keys_num)
-		syslog (LOG_WARNING, "Plugin `%s' did not register for value `%s'.", type, key);
+		WARNING ("Plugin `%s' did not register for value `%s'.", type, key);
 
 	free (key);
 	free (value);
 
-	DBG ("return (%i)", ret);
+	DEBUG ("return (%i)", ret);
 
 	return (ret);
-}
+} /* int cf_dispatch */
 
-void cf_unregister (char *type)
+static int dispatch_global_option (const oconfig_item_t *ci)
 {
-	cf_callback_t *this, *prev;
-
-	for (prev = NULL, this = first_callback;
-			this != NULL;
-			prev = this, this = this->next)
-		if (strcasecmp (this->type, type) == 0)
-		{
-			if (prev == NULL)
-				first_callback = this->next;
-			else
-				prev->next = this->next;
+	if (ci->values_num != 1)
+		return (-1);
+	if (ci->values[0].type == OCONFIG_TYPE_STRING)
+		return (global_option_set (ci->key, ci->values[0].value.string));
+	else if (ci->values[0].type == OCONFIG_TYPE_NUMBER)
+	{
+		char tmp[128];
+		snprintf (tmp, sizeof (tmp), "%lf", ci->values[0].value.number);
+		tmp[127] = '\0';
+		return (global_option_set (ci->key, tmp));
+	}
 
-			free (this);
-			break;
-		}
-}
+	return (-1);
+} /* int dispatch_global_option */
 
-void cf_register (char *type,
-		int (*callback) (char *, char *),
-		char **keys, int keys_num)
+static int dispatch_value_plugindir (const oconfig_item_t *ci)
 {
-	cf_callback_t *cf_cb;
-	char buf[64];
-	int i;
-
-	/* Remove this module from the list, if it already exists */
-	cf_unregister (type);
-
-	/* This pointer will be free'd in `cf_unregister' */
-	if ((cf_cb = (cf_callback_t *) malloc (sizeof (cf_callback_t))) == NULL)
-		return;
-
-	cf_cb->type     = type;
-	cf_cb->callback = callback;
-	cf_cb->keys     = keys;
-	cf_cb->keys_num = keys_num;
-
-	cf_cb->next = first_callback;
-	first_callback = cf_cb;
+	assert (strcasecmp (ci->key, "PluginDir") == 0);
+	
+	if (ci->values_num != 1)
+		return (-1);
+	if (ci->values[0].type != OCONFIG_TYPE_STRING)
+		return (-1);
 
-	for (i = 0; i < keys_num; i++)
-	{
-		if (snprintf (buf, 64, "Plugin.%s", keys[i]) < 64)
-		{
-			/* This may be called multiple times for the same
-			 * `key', but apparently `lc_register_*' can handle
-			 * it.. */
-			lc_register_callback (buf, SHORTOPT_NONE,
-					LC_VAR_STRING, cf_callback_plugin_dispatch,
-					NULL);
-		}
-		else
-		{
-			DBG ("Key was truncated: `%s'", ESCAPE_NULL(keys[i]));
-		}
-	}
+	plugin_set_dir (ci->values[0].value.string);
+	return (0);
 }
 
-/*
- * Other query functions
- */
-char *cf_get_option (const char *key, char *def)
+static int dispatch_value_loadplugin (const oconfig_item_t *ci)
 {
-	int i;
-
-	for (i = 0; i < cf_mode_num; i++)
-	{
-		if ((cf_mode_list[i].mode & operating_mode) == 0)
-			continue;
+	assert (strcasecmp (ci->key, "LoadPlugin") == 0);
 
-		if (strcasecmp (cf_mode_list[i].key, key) != 0)
-			continue;
+	if (ci->values_num != 1)
+		return (-1);
+	if (ci->values[0].type != OCONFIG_TYPE_STRING)
+		return (-1);
 
-		if (cf_mode_list[i].value != NULL)
-			return (cf_mode_list[i].value);
-		return (def);
-	}
+	return (plugin_load (ci->values[0].value.string));
+} /* int dispatch_value_loadplugin */
 
-	return (NULL);
-}
+static int dispatch_value_plugin (const char *plugin, oconfig_item_t *ci)
+{
+	char  buffer[4096];
+	char *buffer_ptr;
+	int   buffer_free;
+	int i;
 
-/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
- * Functions for the actual parsing                                    *
- * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
+	buffer_ptr = buffer;
+	buffer_free = sizeof (buffer);
 
-/*
- * `cf_callback_mode'
- *   Chose the `operating_mode'
- *
- * Mode `value'
- */
-static int cf_callback_mode (const char *shortvar, const char *var,
-		const char *arguments, const char *value, lc_flags_t flags,
-		void *extra)
-{
-	DEBUG_CALLBACK (shortvar, var, arguments, value);
-
-	if (strcasecmp (value, "Client") == 0)
-		operating_mode = MODE_CLIENT;
-#if HAVE_LIBRRD
-	else if (strcasecmp (value, "Server") == 0)
-		operating_mode = MODE_SERVER;
-	else if (strcasecmp (value, "Local") == 0)
-		operating_mode = MODE_LOCAL;
-#else /* !HAVE_LIBRRD */
-	else if (strcasecmp (value, "Server") == 0)
-	{
-		fprintf (stderr, "Invalid mode `Server': "
-				"You need to link against librrd for this "
-				"mode to be available.\n");
-		syslog (LOG_ERR, "Invalid mode `Server': "
-				"You need to link against librrd for this "
-				"mode to be available.");
-		return (LC_CBRET_ERROR);
-	}
-	else if (strcasecmp (value, "Local") == 0)
-	{
-		fprintf (stderr, "Invalid mode `Local': "
-				"You need to link against librrd for this "
-				"mode to be available.\n");
-		syslog (LOG_ERR, "Invalid mode `Local': "
-				"You need to link against librrd for this "
-				"mode to be available.");
-		return (LC_CBRET_ERROR);
-	}
-#endif
-	else if (strcasecmp (value, "Log") == 0)
-		operating_mode = MODE_LOG;
-	else
+	for (i = 0; i < ci->values_num; i++)
 	{
-		syslog (LOG_ERR, "Invalid value for config option `Mode': `%s'", value);
-		return (LC_CBRET_ERROR);
-	}
-
-	return (LC_CBRET_OKAY);
-}
-
-/*
- * `cf_callback_mode_plugindir'
- *   Change the plugin directory
- *
- * <Mode xxx>
- *   PluginDir `value'
- * </Mode>
- */
-static int cf_callback_mode_plugindir (const char *shortvar, const char *var,
-		const char *arguments, const char *value, lc_flags_t flags,
-		void *extra)
-{
-	DEBUG_CALLBACK (shortvar, var, arguments, value);
+		int status = -1;
 
-	plugin_set_dir (value);
+		if (ci->values[i].type == OCONFIG_TYPE_STRING)
+			status = snprintf (buffer_ptr, buffer_free, " %s",
+					ci->values[i].value.string);
+		else if (ci->values[i].type == OCONFIG_TYPE_NUMBER)
+			status = snprintf (buffer_ptr, buffer_free, " %lf",
+					ci->values[i].value.number);
+		else if (ci->values[i].type == OCONFIG_TYPE_BOOLEAN)
+			status = snprintf (buffer_ptr, buffer_free, " %s",
+					ci->values[i].value.boolean
+					? "true" : "false");
+
+		if ((status < 0) || (status >= buffer_free))
+			return (-1);
+		buffer_free -= status;
+		buffer_ptr  += status;
+	}
+	/* skip the initial space */
+	buffer_ptr = buffer + 1;
 
-	return (LC_CBRET_OKAY);
-}
+	return (cf_dispatch (plugin, ci->key, buffer_ptr));
+} /* int plugin_conf_dispatch */
 
-static int cf_callback_mode_option (const char *shortvar, const char *var,
-		const char *arguments, const char *value, lc_flags_t flags,
-		void *extra)
+static int dispatch_value (const oconfig_item_t *ci)
 {
-	cf_mode_item_t *item;
+	int ret = -2;
+	int i;
 
-	DEBUG_CALLBACK (shortvar, var, arguments, value);
+	for (i = 0; i < cf_value_map_num; i++)
+		if (strcasecmp (cf_value_map[i].key, ci->key) == 0)
+		{
+			ret = cf_value_map[i].func (ci);
+			break;
+		}
 
-	if (extra == NULL)
-	{
-		fprintf (stderr, "No extra..?\n");
-		return (LC_CBRET_ERROR);
-	}
+	for (i = 0; i < cf_global_options_num; i++)
+		if (strcasecmp (cf_global_options[i].key, ci->key) == 0)
+		{
+			ret = dispatch_global_option (ci);
+			break;
+		}
 
-	item = (cf_mode_item_t *) extra;
+	return (ret);
+} /* int dispatch_value */
 
-	if (strcasecmp (item->key, shortvar))
-	{
-		fprintf (stderr, "Wrong extra..\n");
-		return (LC_CBRET_ERROR);
-	}
+static int dispatch_block_plugin (oconfig_item_t *ci)
+{
+	int i;
+	char *name;
 
-	if ((operating_mode & item->mode) == 0)
-	{
-		fprintf (stderr, "Option `%s' is not valid in this mode!\n", shortvar);
-		return (LC_CBRET_ERROR);
-	}
+	if (strcasecmp (ci->key, "Plugin") != 0)
+		return (-1);
+	if (ci->values_num != 1)
+		return (-1);
+	if (ci->values[0].type != OCONFIG_TYPE_STRING)
+		return (-1);
 
-	if (item->value != NULL)
-	{
-		free (item->value);
-		item->value = NULL;
-	}
+	name = ci->values[0].value.string;
 
-	if ((item->value = strdup (value)) == NULL)
+	for (i = 0; i < ci->children_num; i++)
 	{
-		perror ("strdup");
-		return (LC_CBRET_ERROR);
+		if (ci->children[i].children == NULL)
+			dispatch_value_plugin (name, ci->children + i);
+		else
+			{DEBUG ("No nested config blocks allow for plugins. Yet.");}
 	}
 
-	return (LC_CBRET_OKAY);
+	return (0);
 }
 
-/*
- * `cf_callback_mode_loadmodule':
- *   Load a plugin.
- *
- * <Mode xxx>
- *   LoadPlugin `value'
- * </Mode>
- */
-static int cf_callback_mode_loadmodule (const char *shortvar, const char *var,
-		const char *arguments, const char *value, lc_flags_t flags,
-		void *extra)
-{
-	DEBUG_CALLBACK (shortvar, var, arguments, value);
-
-	if (plugin_load (value))
-		syslog (LOG_ERR, "plugin_load (%s): failed to load plugin", value);
-
-	/* Return `okay' even if there was an error, because it's not a syntax
-	 * problem.. */
-	return (LC_CBRET_OKAY);
-}
 
-static int cf_callback_socket (const char *shortvar, const char *var,
-		const char *arguments, const char *value, lc_flags_t flags,
-		void *extra)
+static int dispatch_block (oconfig_item_t *ci)
 {
-	char *buffer;
-
-	char *fields[3];
-	int   numfields;
+	if (strcasecmp (ci->key, "Plugin") == 0)
+		return (dispatch_block_plugin (ci));
 
-	char *node;
-	char *service = NET_DEFAULT_PORT;
+	return (0);
+}
 
-	DEBUG_CALLBACK (shortvar, var, arguments, value);
+/* 
+ * Public functions
+ */
+int global_option_set (const char *option, const char *value)
+{
+	int i;
 
-	buffer = strdup (value);
-	if (buffer == NULL)
-		return (LC_CBRET_ERROR);
+	DEBUG ("option = %s; value = %s;", option, value);
 
-	numfields = strsplit (buffer, fields, 3);
+	for (i = 0; i < cf_global_options_num; i++)
+		if (strcasecmp (cf_global_options[i].key, option) == 0)
+			break;
 
-	if ((numfields != 1) && (numfields != 2))
-	{
-		syslog (LOG_ERR, "Invalid number of arguments to `%s'",
-				shortvar);
-		free (buffer);
-		return (LC_CBRET_ERROR);
-	}
+	if (i >= cf_global_options_num)
+		return (-1);
 
-	node = fields[0];
-	if (numfields == 2)
-		service = fields[1];
-
-	/* Still return `LC_CBRET_OKAY' because this is not an syntax error */
-	if (network_create_socket (node, service) < 1)
-		syslog (LOG_ERR, "network_create_socket (%s, %s) failed",
-				node, service);
+	sfree (cf_global_options[i].value);
 
-	free (buffer);
+	if (value != NULL)
+		cf_global_options[i].value = strdup (value);
+	else
+		cf_global_options[i].value = NULL;
 
-	return (LC_CBRET_OKAY);
+	return (0);
 }
 
-/*
- * `cf_callback_plugin'
- *   Start/end section `plugin'
- *
- * <Plugin `arguments'>
- *   ...
- * </Plugin>
- */
-static int cf_callback_plugin (const char *shortvar, const char *var,
-		const char *arguments, const char *value, lc_flags_t flags,
-		void *extra)
+const char *global_option_get (const char *option)
 {
-	DEBUG_CALLBACK (shortvar, var, arguments, value);
-
-	if (flags == LC_FLAGS_SECTIONSTART)
-	{
-		if (nesting_depth != 0)
-		{
-			fprintf (stderr, ERR_NOT_NESTED);
-			return (LC_CBRET_ERROR);
-		}
+	int i;
 
-		if (arguments == NULL)
-		{
-			fprintf (stderr, ERR_NEEDS_ARG, shortvar);
-			return (LC_CBRET_ERROR);
-		}
+	for (i = 0; i < cf_global_options_num; i++)
+		if (strcasecmp (cf_global_options[i].key, option) == 0)
+			break;
 
-		if ((current_module = strdup (arguments)) == NULL)
-		{
-			perror ("strdup");
-			return (LC_CBRET_ERROR);
-		}
+	if (i >= cf_global_options_num)
+		return (NULL);
+	
+	return ((cf_global_options[i].value != NULL)
+			? cf_global_options[i].value
+			: cf_global_options[i].def);
+} /* char *global_option_get */
 
-		nesting_depth++;
+void cf_unregister (const char *type)
+{
+	cf_callback_t *this, *prev;
 
-		if (cf_search (current_module) != NULL)
-			return (LC_CBRET_OKAY);
-		else
-			return (LC_CBRET_IGNORESECTION);
-	}
-	else if (flags == LC_FLAGS_SECTIONEND)
-	{
-		if (current_module != NULL)
+	for (prev = NULL, this = first_callback;
+			this != NULL;
+			prev = this, this = this->next)
+		if (strcasecmp (this->type, type) == 0)
 		{
-			free (current_module);
-			current_module = NULL;
-		}
-
-		nesting_depth--;
+			if (prev == NULL)
+				first_callback = this->next;
+			else
+				prev->next = this->next;
 
-		return (LC_CBRET_OKAY);
-	}
-	else
-	{
-		fprintf (stderr, ERR_SECTION_ONLY, shortvar);
-		return (LC_CBRET_ERROR);
-	}
-}
+			free (this);
+			break;
+		}
+} /* void cf_unregister */
 
-/*
- * `cf_callback_plugin_dispatch'
- *   Send options within `plugin' sections to the plugin that requests it.
- *
- * <Plugin `current_module'>
- *   `var' `value'
- * </Plugin>
- */
-static int cf_callback_plugin_dispatch (const char *shortvar, const char *var,
-		const char *arguments, const char *value, lc_flags_t flags,
-		void *extra)
+void cf_register (const char *type,
+		int (*callback) (const char *, const char *),
+		const char **keys, int keys_num)
 {
-	DEBUG_CALLBACK (shortvar, var, arguments, value);
-
-	if ((nesting_depth == 0) || (current_module == NULL))
-	{
-		fprintf (stderr, ERR_NEEDS_SECTION, shortvar);
-		return (LC_CBRET_ERROR);
-	}
-
-	/* Send the data to the plugin */
-	if (cf_dispatch (current_module, shortvar, value) < 0)
-		return (LC_CBRET_ERROR);
-
-	return (LC_CBRET_OKAY);
-}
+	cf_callback_t *cf_cb;
 
-static void cf_init (void)
-{
-	static int run_once = 0;
-	int i;
+	/* Remove this module from the list, if it already exists */
+	cf_unregister (type);
 
-	if (run_once != 0)
+	/* This pointer will be free'd in `cf_unregister' */
+	if ((cf_cb = (cf_callback_t *) malloc (sizeof (cf_callback_t))) == NULL)
 		return;
-	run_once = 1;
-
-	lc_register_callback ("Mode", SHORTOPT_NONE, LC_VAR_STRING,
-			cf_callback_mode, NULL);
-	lc_register_callback ("Plugin", SHORTOPT_NONE, LC_VAR_SECTION,
-			cf_callback_plugin, NULL);
-
-	lc_register_callback ("PluginDir", SHORTOPT_NONE,
-			LC_VAR_STRING, cf_callback_mode_plugindir, NULL);
-	lc_register_callback ("LoadPlugin", SHORTOPT_NONE,
-			LC_VAR_STRING, cf_callback_mode_loadmodule, NULL);
-
-	lc_register_callback ("Listen", SHORTOPT_NONE,
-			LC_VAR_STRING, cf_callback_socket, NULL);
-	lc_register_callback ("Server", SHORTOPT_NONE,
-			LC_VAR_STRING, cf_callback_socket, NULL);
 
-	for (i = 0; i < cf_mode_num; i++)
-	{
-		cf_mode_item_t *item;
-
-		item = &cf_mode_list[i];
+	cf_cb->type     = type;
+	cf_cb->callback = callback;
+	cf_cb->keys     = keys;
+	cf_cb->keys_num = keys_num;
 
-		lc_register_callback (item->key, SHORTOPT_NONE, LC_VAR_STRING,
-				cf_callback_mode_option, (void *) item);
-	}
-}
+	cf_cb->next = first_callback;
+	first_callback = cf_cb;
+} /* void cf_register */
 
 int cf_read (char *filename)
 {
-	cf_init ();
-
-	if (filename == NULL)
-		filename = CONFIGFILE;
-
-	DBG ("Starting to parse file `%s'", filename);
+	oconfig_item_t *conf;
+	int i;
 
-	/* int lc_process_file(const char *appname, const char *pathname, lc_conf_type_t type); */
-	if (lc_process_file ("collectd", filename, LC_CONF_APACHE))
+	conf = oconfig_parse_file (filename);
+	if (conf == NULL)
 	{
-		syslog (LOG_ERR, "lc_process_file (%s): %s", filename, lc_geterrstr ());
+		ERROR ("Unable to read config file %s.", filename);
 		return (-1);
 	}
 
-	DBG ("Done parsing file `%s'", filename);
-
-	/* free memory and stuff */
-	lc_cleanup ();
+	for (i = 0; i < conf->children_num; i++)
+	{
+		if (conf->children[i].children == NULL)
+			dispatch_value (conf->children + i);
+		else
+			dispatch_block (conf->children + i);
+	}
 
 	return (0);
-}
+} /* int cf_read */

			ret = (*cf_cb->callback) (key, value);
			break;
		}
	}

	if (i >= cf_cb->keys_num)
		WARNING ("Plugin `%s' did not register for value `%s'.", type, key);

	free (key);
	free (value);

	DEBUG ("return (%i)", ret);

	return (ret);
} /* int cf_dispatch */

static int dispatch_global_option (const oconfig_item_t *ci)
{
	if (ci->values_num != 1)
		return (-1);
	if (ci->values[0].type == OCONFIG_TYPE_STRING)
		return (global_option_set (ci->key, ci->values[0].value.string));
	else if (ci->values[0].type == OCONFIG_TYPE_NUMBER)
	{
		char tmp[128];
		snprintf (tmp, sizeof (tmp), "%lf", ci->values[0].value.number);
		tmp[127] = '\0';
		return (global_option_set (ci->key, tmp));
	}

	return (-1);
} /* int dispatch_global_option */

static int dispatch_value_plugindir (const oconfig_item_t *ci)
{
	assert (strcasecmp (ci->key, "PluginDir") == 0);
	
	if (ci->values_num != 1)
		return (-1);
	if (ci->values[0].type != OCONFIG_TYPE_STRING)
		return (-1);

	plugin_set_dir (ci->values[0].value.string);
	return (0);
}

static int dispatch_value_loadplugin (const oconfig_item_t *ci)
{
	assert (strcasecmp (ci->key, "LoadPlugin") == 0);

	if (ci->values_num != 1)
		return (-1);
	if (ci->values[0].type != OCONFIG_TYPE_STRING)
		return (-1);

	return (plugin_load (ci->values[0].value.string));
} /* int dispatch_value_loadplugin */

static int dispatch_value_plugin (const char *plugin, oconfig_item_t *ci)
{
	char  buffer[4096];
	char *buffer_ptr;
	int   buffer_free;
	int i;

	buffer_ptr = buffer;
	buffer_free = sizeof (buffer);

	for (i = 0; i < ci->values_num; i++)
	{
		int status = -1;

		if (ci->values[i].type == OCONFIG_TYPE_STRING)
			status = snprintf (buffer_ptr, buffer_free, " %s",
					ci->values[i].value.string);
		else if (ci->values[i].type == OCONFIG_TYPE_NUMBER)
			status = snprintf (buffer_ptr, buffer_free, " %lf",
					ci->values[i].value.number);
		else if (ci->values[i].type == OCONFIG_TYPE_BOOLEAN)
			status = snprintf (buffer_ptr, buffer_free, " %s",
					ci->values[i].value.boolean
					? "true" : "false");

		if ((status < 0) || (status >= buffer_free))
			return (-1);
		buffer_free -= status;
		buffer_ptr  += status;
	}
	/* skip the initial space */
	buffer_ptr = buffer + 1;

	return (cf_dispatch (plugin, ci->key, buffer_ptr));
} /* int plugin_conf_dispatch */

static int dispatch_value (const oconfig_item_t *ci)
{
	int ret = -2;
	int i;

	for (i = 0; i < cf_value_map_num; i++)
		if (strcasecmp (cf_value_map[i].key, ci->key) == 0)
		{
			ret = cf_value_map[i].func (ci);
			break;
		}

	for (i = 0; i < cf_global_options_num; i++)
		if (strcasecmp (cf_global_options[i].key, ci->key) == 0)
		{
			ret = dispatch_global_option (ci);
			break;
		}

	return (ret);
} /* int dispatch_value */

static int dispatch_block_plugin (oconfig_item_t *ci)
{
	int i;
	char *name;

	if (strcasecmp (ci->key, "Plugin") != 0)
		return (-1);
	if (ci->values_num != 1)
		return (-1);
	if (ci->values[0].type != OCONFIG_TYPE_STRING)
		return (-1);

	name = ci->values[0].value.string;

	for (i = 0; i < ci->children_num; i++)
	{
		if (ci->children[i].children == NULL)
			dispatch_value_plugin (name, ci->children + i);
		else
			{DEBUG ("No nested config blocks allow for plugins. Yet.");}
	}

	return (0);
}


static int dispatch_block (oconfig_item_t *ci)
{
	if (strcasecmp (ci->key, "Plugin") == 0)
		return (dispatch_block_plugin (ci));

	return (0);
}

/* 
 * Public functions
 */
int global_option_set (const char *option, const char *value)
{
	int i;

	DEBUG ("option = %s; value = %s;", option, value);

	for (i = 0; i < cf_global_options_num; i++)
		if (strcasecmp (cf_global_options[i].key, option) == 0)
			break;

	if (i >= cf_global_options_num)
		return (-1);

	sfree (cf_global_options[i].value);

	if (value != NULL)
		cf_global_options[i].value = strdup (value);
	else
		cf_global_options[i].value = NULL;

	return (0);
}

const char *global_option_get (const char *option)
{
	int i;

	for (i = 0; i < cf_global_options_num; i++)
		if (strcasecmp (cf_global_options[i].key, option) == 0)
			break;

	if (i >= cf_global_options_num)
		return (NULL);
	
	return ((cf_global_options[i].value != NULL)
			? cf_global_options[i].value
			: cf_global_options[i].def);
} /* char *global_option_get */

void cf_unregister (const char *type)
{
	cf_callback_t *this, *prev;

	for (prev = NULL, this = first_callback;
			this != NULL;
			prev = this, this = this->next)
		if (strcasecmp (this->type, type) == 0)
		{
			if (prev == NULL)
				first_callback = this->next;
			else
				prev->next = this->next;

			free (this);
			break;
		}
} /* void cf_unregister */

void cf_register (const char *type,
		int (*callback) (const char *, const char *),
		const char **keys, int keys_num)
{
	cf_callback_t *cf_cb;

	/* Remove this module from the list, if it already exists */
	cf_unregister (type);

	/* This pointer will be free'd in `cf_unregister' */
	if ((cf_cb = (cf_callback_t *) malloc (sizeof (cf_callback_t))) == NULL)
		return;

	cf_cb->type     = type;
	cf_cb->callback = callback;
	cf_cb->keys     = keys;
	cf_cb->keys_num = keys_num;

	cf_cb->next = first_callback;
	first_callback = cf_cb;
} /* void cf_register */

int cf_read (char *filename)
{
	oconfig_item_t *conf;
	int i;

	conf = oconfig_parse_file (filename);
	if (conf == NULL)
	{
		ERROR ("Unable to read config file %s.", filename);
		return (-1);
	}

	for (i = 0; i < conf->children_num; i++)
	{
		if (conf->children[i].children == NULL)
			dispatch_value (conf->children + i);
		else
			dispatch_block (conf->children + i);
	}

	return (0);
} /* int cf_read */

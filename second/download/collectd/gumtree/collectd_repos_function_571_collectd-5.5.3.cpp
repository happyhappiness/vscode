static char *sensu_notification_to_json(struct sensu_host *host, /* {{{ */
		notification_t const *n)
{
	char service_buffer[6 * DATA_MAX_NAME_LEN];
	char const *severity;
	notification_meta_t *meta;
	char *ret_str;
	char *temp_str;
	int status;
	int i;
	int res;
	// add the severity/status
	switch (n->severity) {
		case NOTIF_OKAY:
			severity = "OK";
			status = 0;
			break;
		case NOTIF_WARNING:
			severity = "WARNING";
			status = 1;
			break;
		case NOTIF_FAILURE:
			severity = "CRITICAL";
			status = 2;
			break;
		default:
			severity = "UNKNOWN";
			status = 3;
	}
	res = asprintf(&temp_str, "{\"status\": %d", status);
	if (res == -1) {
		ERROR("write_sensu plugin: Unable to alloc memory");
		return NULL;
	}
	ret_str = temp_str;

	// incorporate the timestamp
	res = asprintf(&temp_str, "%s, \"timestamp\": %ld", ret_str, CDTIME_T_TO_TIME_T(n->time));
	free(ret_str);
	if (res == -1) {
		ERROR("write_sensu plugin: Unable to alloc memory");
		return NULL;
	}
	ret_str = temp_str;

	char *handlers_str = build_json_str_list("handlers", &(host->notification_handlers));
	if (handlers_str == NULL) {
		ERROR("write_sensu plugin: Unable to alloc memory");
		free(ret_str);
		return NULL;
	}
	// incorporate the handlers
	if (strlen(handlers_str) != 0) {
		res = asprintf(&temp_str, "%s, %s", ret_str, handlers_str);
		free(ret_str);
		free(handlers_str);
		if (res == -1) {
			ERROR("write_sensu plugin: Unable to alloc memory");
			return NULL;
		}
		ret_str = temp_str;
	} else {
		free(handlers_str);
	}

	// incorporate the plugin name information if any
	if (n->plugin[0] != 0) {
		res = asprintf(&temp_str, "%s, \"collectd_plugin\": \"%s\"", ret_str, n->plugin);
		free(ret_str);
		if (res == -1) {
			ERROR("write_sensu plugin: Unable to alloc memory");
			return NULL;
		}
		ret_str = temp_str;
	}

	// incorporate the plugin type if any
	if (n->type[0] != 0) {
		res = asprintf(&temp_str, "%s, \"collectd_plugin_type\": \"%s\"", ret_str, n->type);
		free(ret_str);
		if (res == -1) {
			ERROR("write_sensu plugin: Unable to alloc memory");
			return NULL;
		}
		ret_str = temp_str;
	}

	// incorporate the plugin instance if any
	if (n->plugin_instance[0] != 0) {
		res = asprintf(&temp_str, "%s, \"collectd_plugin_instance\": \"%s\"", ret_str, n->plugin_instance);
		free(ret_str);
		if (res == -1) {
			ERROR("write_sensu plugin: Unable to alloc memory");
			return NULL;
		}
		ret_str = temp_str;
	}

	// incorporate the plugin type instance if any
	if (n->type_instance[0] != 0) {
		res = asprintf(&temp_str, "%s, \"collectd_plugin_type_instance\": \"%s\"", ret_str, n->type_instance);
		free(ret_str);
		if (res == -1) {
			ERROR("write_sensu plugin: Unable to alloc memory");
			return NULL;
		}
		ret_str = temp_str;
	}

	// add key value attributes from config if any
	for (i = 0; i < sensu_attrs_num; i += 2) {
		res = asprintf(&temp_str, "%s, \"%s\": \"%s\"", ret_str, sensu_attrs[i], sensu_attrs[i+1]);
		free(ret_str);
		if (res == -1) {
			ERROR("write_sensu plugin: Unable to alloc memory");
			return NULL;
		}
		ret_str = temp_str;
	}

	// incorporate sensu tags from config if any
	if ((sensu_tags != NULL) && (strlen(sensu_tags) != 0)) {
		res = asprintf(&temp_str, "%s, %s", ret_str, sensu_tags);
		free(ret_str);
		if (res == -1) {
			ERROR("write_sensu plugin: Unable to alloc memory");
			return NULL;
		}
		ret_str = temp_str;
	}

	// incorporate the service name
	sensu_format_name2(service_buffer, sizeof(service_buffer),
				/* host */ "", n->plugin, n->plugin_instance,
				n->type, n->type_instance, host->separator);
	// replace sensu event name chars that are considered illegal
	in_place_replace_sensu_name_reserved(service_buffer);
	res = asprintf(&temp_str, "%s, \"name\": \"%s\"", ret_str, &service_buffer[1]);
	free(ret_str);
	if (res == -1) {
		ERROR("write_sensu plugin: Unable to alloc memory");
		return NULL;
	}
	ret_str = temp_str;

	// incorporate the check output
	if (n->message[0] != 0) {
		char *msg = replace_json_reserved(n->message);
		if (msg == NULL) {
			ERROR("write_sensu plugin: Unable to alloc memory");
			free(ret_str);
			return NULL;
		}
		res = asprintf(&temp_str, "%s, \"output\": \"%s - %s\"", ret_str, severity, msg);
		free(ret_str);
		free(msg);
		if (res == -1) {
			ERROR("write_sensu plugin: Unable to alloc memory");
			return NULL;
		}
		ret_str = temp_str;
	}

	// Pull in values from threshold and add extra attributes
	for (meta = n->meta; meta != NULL; meta = meta->next) {
		if (strcasecmp("CurrentValue", meta->name) == 0 && meta->type == NM_TYPE_DOUBLE) {
			res = asprintf(&temp_str, "%s, \"current_value\": \"%.8f\"", ret_str, meta->nm_value.nm_double);
			free(ret_str);
			if (res == -1) {
				ERROR("write_sensu plugin: Unable to alloc memory");
				return NULL;
			}
			ret_str = temp_str;
		}
		if (meta->type == NM_TYPE_STRING) {
			res = asprintf(&temp_str, "%s, \"%s\": \"%s\"", ret_str, meta->name, meta->nm_value.nm_string);
			free(ret_str);
			if (res == -1) {
				ERROR("write_sensu plugin: Unable to alloc memory");
				return NULL;
			}
			ret_str = temp_str;
		}
	}

	// close the curly bracket
	res = asprintf(&temp_str, "%s}\n", ret_str);
	free(ret_str);
	if (res == -1) {
		ERROR("write_sensu plugin: Unable to alloc memory");
		return NULL;
	}
	ret_str = temp_str;

	DEBUG("write_sensu plugin: Successfully created JSON for notification: "
				"host = \"%s\", service = \"%s\", state = \"%s\"",
				n->host, service_buffer, severity);
	return ret_str;
}
static char *sensu_value_to_json(struct sensu_host const *host, /* {{{ */
		data_set_t const *ds,
		value_list_t const *vl, size_t index,
		gauge_t const *rates,
		int status)
{
	char name_buffer[5 * DATA_MAX_NAME_LEN];
	char service_buffer[6 * DATA_MAX_NAME_LEN];
	char *ret_str;
	char *temp_str;
	char *value_str;
	int res;
	// First part of the JSON string
	const char *part1 = "{\"name\": \"collectd\", \"type\": \"metric\"";

	char *handlers_str = build_json_str_list("handlers", &(host->metric_handlers));
	if (handlers_str == NULL) {
		ERROR("write_sensu plugin: Unable to alloc memory");
		return NULL;
	}

	// incorporate the handlers
	if (strlen(handlers_str) == 0) {
		free(handlers_str);
		ret_str = strdup(part1);
		if (ret_str == NULL) {
			ERROR("write_sensu plugin: Unable to alloc memory");
			return NULL;
		}
	}
	else {
		res = my_asprintf(&ret_str, "%s, %s", part1, handlers_str);
		free(handlers_str);
		if (res == -1) {
			ERROR("write_sensu plugin: Unable to alloc memory");
			return NULL;
		}
	}

	// incorporate the plugin name information
	res = my_asprintf(&temp_str, "%s, \"collectd_plugin\": \"%s\"", ret_str, vl->plugin);
	free(ret_str);
	if (res == -1) {
		ERROR("write_sensu plugin: Unable to alloc memory");
		return NULL;
	}
	ret_str = temp_str;

	// incorporate the plugin type
	res = my_asprintf(&temp_str, "%s, \"collectd_plugin_type\": \"%s\"", ret_str, vl->type);
	free(ret_str);
	if (res == -1) {
		ERROR("write_sensu plugin: Unable to alloc memory");
		return NULL;
	}
	ret_str = temp_str;

	// incorporate the plugin instance if any
	if (vl->plugin_instance[0] != 0) {
		res = my_asprintf(&temp_str, "%s, \"collectd_plugin_instance\": \"%s\"", ret_str, vl->plugin_instance);
		free(ret_str);
		if (res == -1) {
			ERROR("write_sensu plugin: Unable to alloc memory");
			return NULL;
		}
		ret_str = temp_str;
	}

	// incorporate the plugin type instance if any
	if (vl->type_instance[0] != 0) {
		res = my_asprintf(&temp_str, "%s, \"collectd_plugin_type_instance\": \"%s\"", ret_str, vl->type_instance);
		free(ret_str);
		if (res == -1) {
			ERROR("write_sensu plugin: Unable to alloc memory");
			return NULL;
		}
		ret_str = temp_str;
	}

	// incorporate the data source type
	if ((ds->ds[index].type != DS_TYPE_GAUGE) && (rates != NULL)) {
		char ds_type[DATA_MAX_NAME_LEN];
		ssnprintf (ds_type, sizeof (ds_type), "%s:rate", DS_TYPE_TO_STRING(ds->ds[index].type));
		res = my_asprintf(&temp_str, "%s, \"collectd_data_source_type\": \"%s\"", ret_str, ds_type);
		free(ret_str);
		if (res == -1) {
			ERROR("write_sensu plugin: Unable to alloc memory");
			return NULL;
		}
		ret_str = temp_str;
	} else {
		res = my_asprintf(&temp_str, "%s, \"collectd_data_source_type\": \"%s\"", ret_str, DS_TYPE_TO_STRING(ds->ds[index].type));
		free(ret_str);
		if (res == -1) {
			ERROR("write_sensu plugin: Unable to alloc memory");
			return NULL;
		}
		ret_str = temp_str;
	}

	// incorporate the data source name
	res = my_asprintf(&temp_str, "%s, \"collectd_data_source_name\": \"%s\"", ret_str, ds->ds[index].name);
	free(ret_str);
	if (res == -1) {
		ERROR("write_sensu plugin: Unable to alloc memory");
		return NULL;
	}
	ret_str = temp_str;

	// incorporate the data source index
	{
		char ds_index[DATA_MAX_NAME_LEN];
		ssnprintf (ds_index, sizeof (ds_index), "%zu", index);
		res = my_asprintf(&temp_str, "%s, \"collectd_data_source_index\": %s", ret_str, ds_index);
		free(ret_str);
		if (res == -1) {
			ERROR("write_sensu plugin: Unable to alloc memory");
			return NULL;
		}
		ret_str = temp_str;
	}

	// add key value attributes from config if any
	for (size_t i = 0; i < sensu_attrs_num; i += 2) {
		res = my_asprintf(&temp_str, "%s, \"%s\": \"%s\"", ret_str, sensu_attrs[i], sensu_attrs[i+1]);
		free(ret_str);
		if (res == -1) {
			ERROR("write_sensu plugin: Unable to alloc memory");
			return NULL;
		}
		ret_str = temp_str;
	}

	// incorporate sensu tags from config if any
	if ((sensu_tags != NULL) && (strlen(sensu_tags) != 0)) {
		res = my_asprintf(&temp_str, "%s, %s", ret_str, sensu_tags);
		free(ret_str);
		if (res == -1) {
			ERROR("write_sensu plugin: Unable to alloc memory");
			return NULL;
		}
		ret_str = temp_str;
	}

	// calculate the value and set to a string
	if (ds->ds[index].type == DS_TYPE_GAUGE) {
		res = my_asprintf(&value_str, GAUGE_FORMAT, vl->values[index].gauge);
		if (res == -1) {
			free(ret_str);
			ERROR("write_sensu plugin: Unable to alloc memory");
			return NULL;
		}
	} else if (rates != NULL) {
		res = my_asprintf(&value_str, GAUGE_FORMAT, rates[index]);
		if (res == -1) {
			free(ret_str);
			ERROR("write_sensu plugin: Unable to alloc memory");
			return NULL;
		}
	} else {
		if (ds->ds[index].type == DS_TYPE_DERIVE) {
			res = my_asprintf(&value_str, "%"PRIi64, vl->values[index].derive);
			if (res == -1) {
				free(ret_str);
				ERROR("write_sensu plugin: Unable to alloc memory");
				return NULL;
			}
		}
		else if (ds->ds[index].type == DS_TYPE_ABSOLUTE) {
			res = my_asprintf(&value_str, "%"PRIu64, vl->values[index].absolute);
			if (res == -1) {
				free(ret_str);
				ERROR("write_sensu plugin: Unable to alloc memory");
				return NULL;
			}
		}
		else {
			res = my_asprintf(&value_str, "%llu", vl->values[index].counter);
			if (res == -1) {
				free(ret_str);
				ERROR("write_sensu plugin: Unable to alloc memory");
				return NULL;
			}
		}
	}

	// Generate the full service name
	sensu_format_name2(name_buffer, sizeof(name_buffer),
		vl->host, vl->plugin, vl->plugin_instance,
		vl->type, vl->type_instance, host->separator);
	if (host->always_append_ds || (ds->ds_num > 1)) {
		if (host->event_service_prefix == NULL)
			ssnprintf(service_buffer, sizeof(service_buffer), "%s.%s",
					name_buffer, ds->ds[index].name);
		else
			ssnprintf(service_buffer, sizeof(service_buffer), "%s%s.%s",
					host->event_service_prefix, name_buffer, ds->ds[index].name);
	} else {
		if (host->event_service_prefix == NULL)
			sstrncpy(service_buffer, name_buffer, sizeof(service_buffer));
		else
			ssnprintf(service_buffer, sizeof(service_buffer), "%s%s",
					host->event_service_prefix, name_buffer);
	}

	// Replace collectd sensor name reserved characters so that time series DB is happy
	in_place_replace_sensu_name_reserved(service_buffer);

	// finalize the buffer by setting the output and closing curly bracket
	res = my_asprintf(&temp_str, "%s, \"output\": \"%s %s %lld\"}\n",ret_str, service_buffer, value_str, (long long)CDTIME_T_TO_TIME_T(vl->time));
	free(ret_str);
	free(value_str);
	if (res == -1) {
		ERROR("write_sensu plugin: Unable to alloc memory");
		return NULL;
	}
	ret_str = temp_str;

	DEBUG("write_sensu plugin: Successfully created json for metric: "
			"host = \"%s\", service = \"%s\"",
			vl->host, service_buffer);
	return ret_str;
}
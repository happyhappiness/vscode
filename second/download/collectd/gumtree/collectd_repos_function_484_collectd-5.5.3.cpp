static char *values_to_sqlarray (const data_set_t *ds, const value_list_t *vl,
		char *string, size_t string_len, _Bool store_rates)
{
	char  *str_ptr;
	size_t str_len;

	gauge_t *rates = NULL;

	int i;

	str_ptr = string;
	str_len = string_len;

	for (i = 0; i < vl->values_len; ++i) {
		int status = 0;

		if ((ds->ds[i].type != DS_TYPE_GAUGE)
				&& (ds->ds[i].type != DS_TYPE_COUNTER)
				&& (ds->ds[i].type != DS_TYPE_DERIVE)
				&& (ds->ds[i].type != DS_TYPE_ABSOLUTE)) {
			log_err ("c_psql_write: Unknown data source type: %i",
					ds->ds[i].type);
			sfree (rates);
			return NULL;
		}

		if (ds->ds[i].type == DS_TYPE_GAUGE)
			status = ssnprintf (str_ptr, str_len,
					","GAUGE_FORMAT, vl->values[i].gauge);
		else if (store_rates) {
			if (rates == NULL)
				rates = uc_get_rate (ds, vl);

			if (rates == NULL) {
				log_err ("c_psql_write: Failed to determine rate");
				return NULL;
			}

			status = ssnprintf (str_ptr, str_len,
					",%lf", rates[i]);
		}
		else if (ds->ds[i].type == DS_TYPE_COUNTER)
			status = ssnprintf (str_ptr, str_len,
					",%llu", vl->values[i].counter);
		else if (ds->ds[i].type == DS_TYPE_DERIVE)
			status = ssnprintf (str_ptr, str_len,
					",%"PRIi64, vl->values[i].derive);
		else if (ds->ds[i].type == DS_TYPE_ABSOLUTE)
			status = ssnprintf (str_ptr, str_len,
					",%"PRIu64, vl->values[i].absolute);

		if (status < 1) {
			str_len = 0;
			break;
		}
		else if ((size_t)status >= str_len) {
			str_len = 0;
			break;
		}
		else {
			str_ptr += status;
			str_len -= (size_t)status;
		}
	}

	sfree (rates);

	if (str_len <= 2) {
		log_err ("c_psql_write: Failed to stringify value list");
		return NULL;
	}

	/* overwrite the first comma */
	string[0] = '{';
	str_ptr[0] = '}';
	str_ptr[1] = '\0';

	return string;
}
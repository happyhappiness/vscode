
	return ret;
}

static char *normalize_value(const char *key, const char *value)
{
	char *normalized;

	if (!value)
		return NULL;

	if (types == 0 || types == TYPE_PATH)
		/*
		 * We don't do normalization for TYPE_PATH here: If
		 * the path is like ~/foobar/, we prefer to store
		 * "~/foobar/" in the config file, and to expand the ~
		 * when retrieving the value.
		 */
		normalized = xstrdup(value);
	else {
		normalized = xmalloc(64);
		if (types == TYPE_INT) {
			int64_t v = git_config_int64(key, value);
			sprintf(normalized, "%"PRId64, v);
		}
		else if (types == TYPE_BOOL)
			sprintf(normalized, "%s",
				git_config_bool(key, value) ? "true" : "false");
		else if (types == TYPE_BOOL_OR_INT) {
			int is_bool, v;
			v = git_config_bool_or_int(key, value, &is_bool);
			if (!is_bool)
				sprintf(normalized, "%d", v);
			else
				sprintf(normalized, "%s", v ? "true" : "false");
		}
	}

	return normalized;
}

static int get_color_found;
static const char *get_color_slot;
static const char *get_colorbool_slot;
static char parsed_color[COLOR_MAXLEN];

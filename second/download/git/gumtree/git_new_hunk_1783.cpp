				dst += sprintf(dst, "48;5;%d", bg);
			}
		}
		*dst++ = 'm';
	}
	*dst = 0;
	return 0;
bad:
	return error(_("invalid color value: %.*s"), value_len, value);
}

int git_config_colorbool(const char *var, const char *value)
{
	if (value) {
		if (!strcasecmp(value, "never"))

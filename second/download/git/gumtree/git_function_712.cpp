static enum protocol_allow_config parse_protocol_config(const char *key,
							const char *value)
{
	if (!strcasecmp(value, "always"))
		return PROTOCOL_ALLOW_ALWAYS;
	else if (!strcasecmp(value, "never"))
		return PROTOCOL_ALLOW_NEVER;
	else if (!strcasecmp(value, "user"))
		return PROTOCOL_ALLOW_USER_ONLY;

	die("unknown value for config '%s': %s", key, value);
}
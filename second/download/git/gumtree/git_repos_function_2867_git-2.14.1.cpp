int parse_decorate_color_config(const char *var, const char *slot_name, const char *value)
{
	int slot = parse_decorate_color_slot(slot_name);
	if (slot < 0)
		return 0;
	if (!value)
		return config_error_nonbool(var);
	return color_parse(value, decoration_colors[slot]);
}
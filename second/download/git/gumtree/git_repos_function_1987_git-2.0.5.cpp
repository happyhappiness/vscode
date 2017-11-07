int parse_decorate_color_config(const char *var, const int ofs, const char *value)
{
	int slot = parse_decorate_color_slot(var + ofs);
	if (slot < 0)
		return 0;
	if (!value)
		return config_error_nonbool(var);
	color_parse(value, var, decoration_colors[slot]);
	return 0;
}
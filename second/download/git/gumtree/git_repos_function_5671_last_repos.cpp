static int log_line_range_callback(const struct option *option, const char *arg, int unset)
{
	struct line_opt_callback_data *data = option->value;

	if (!arg)
		return -1;

	data->rev->line_level_traverse = 1;
	string_list_append(&data->args, arg);

	return 0;
}
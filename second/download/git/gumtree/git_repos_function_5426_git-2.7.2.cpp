static void append_path(struct grep_opt *opt, const void *data, size_t len)
{
	struct string_list *path_list = opt->output_priv;

	if (len == 1 && *(const char *)data == '\0')
		return;
	string_list_append(path_list, xstrndup(data, len));
}
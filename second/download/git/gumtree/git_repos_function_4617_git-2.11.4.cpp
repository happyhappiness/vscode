static int add_man_viewer_path(const char *name,
			       size_t len,
			       const char *value)
{
	if (supported_man_viewer(name, len))
		do_add_man_viewer_info(name, len, value);
	else
		warning(_("'%s': path for unsupported man viewer.\n"
			  "Please consider using 'man.<tool>.cmd' instead."),
			name);

	return 0;
}
void set_diffopt_flags_from_submodule_config(struct diff_options *diffopt,
					     const char *path)
{
	struct string_list_item *path_option, *ignore_option;
	path_option = unsorted_string_list_lookup(&config_name_for_path, path);
	if (path_option) {
		ignore_option = unsorted_string_list_lookup(&config_ignore_for_name, path_option->util);
		if (ignore_option)
			handle_ignore_submodules_arg(diffopt, ignore_option->util);
		else if (gitmodules_is_unmerged)
			DIFF_OPT_SET(diffopt, IGNORE_SUBMODULES);
	}
}
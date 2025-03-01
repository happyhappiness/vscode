int remove_path_from_gitmodules(const char *path)
{
	struct strbuf sect = STRBUF_INIT;
	struct string_list_item *path_option;

	if (!file_exists(".gitmodules")) /* Do nothing without .gitmodules */
		return -1;

	if (gitmodules_is_unmerged)
		die(_("Cannot change unmerged .gitmodules, resolve merge conflicts first"));

	path_option = unsorted_string_list_lookup(&config_name_for_path, path);
	if (!path_option) {
		warning(_("Could not find section in .gitmodules where path=%s"), path);
		return -1;
	}
	strbuf_addstr(&sect, "submodule.");
	strbuf_addstr(&sect, path_option->util);
	if (git_config_rename_section_in_file(".gitmodules", sect.buf, NULL) < 0) {
		/* Maybe the user already did that, don't error out here */
		warning(_("Could not remove .gitmodules entry for %s"), path);
		strbuf_release(&sect);
		return -1;
	}
	strbuf_release(&sect);
	return 0;
}
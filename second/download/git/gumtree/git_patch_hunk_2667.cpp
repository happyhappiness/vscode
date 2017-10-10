  * path is configured. Return 0 only if a .gitmodules file was found, a section
  * with the correct path=<path> setting was found and we could remove it.
  */
 int remove_path_from_gitmodules(const char *path)
 {
 	struct strbuf sect = STRBUF_INIT;
-	struct string_list_item *path_option;
+	const struct submodule *submodule;
 
 	if (!file_exists(".gitmodules")) /* Do nothing without .gitmodules */
 		return -1;
 
 	if (gitmodules_is_unmerged)
 		die(_("Cannot change unmerged .gitmodules, resolve merge conflicts first"));
 
-	path_option = unsorted_string_list_lookup(&config_name_for_path, path);
-	if (!path_option) {
+	submodule = submodule_from_path(null_sha1, path);
+	if (!submodule || !submodule->name) {
 		warning(_("Could not find section in .gitmodules where path=%s"), path);
 		return -1;
 	}
 	strbuf_addstr(&sect, "submodule.");
-	strbuf_addstr(&sect, path_option->util);
+	strbuf_addstr(&sect, submodule->name);
 	if (git_config_rename_section_in_file(".gitmodules", sect.buf, NULL) < 0) {
 		/* Maybe the user already did that, don't error out here */
 		warning(_("Could not remove .gitmodules entry for %s"), path);
 		strbuf_release(&sect);
 		return -1;
 	}

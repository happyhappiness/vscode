 * .gitmodules file. Return 0 only if a .gitmodules file was found, a section
 * with the correct path=<oldpath> setting was found and we could update it.
 */
int update_path_in_gitmodules(const char *oldpath, const char *newpath)
{
	struct strbuf entry = STRBUF_INIT;
	const struct submodule *submodule;

	if (!file_exists(".gitmodules")) /* Do nothing without .gitmodules */
		return -1;

	if (gitmodules_is_unmerged)
		die(_("Cannot change unmerged .gitmodules, resolve merge conflicts first"));

	submodule = submodule_from_path(null_sha1, oldpath);
	if (!submodule || !submodule->name) {
		warning(_("Could not find section in .gitmodules where path=%s"), oldpath);
		return -1;
	}
	strbuf_addstr(&entry, "submodule.");
	strbuf_addstr(&entry, submodule->name);
	strbuf_addstr(&entry, ".path");
	if (git_config_set_in_file(".gitmodules", entry.buf, newpath) < 0) {
		/* Maybe the user already did that, don't error out here */
		warning(_("Could not update .gitmodules entry %s"), entry.buf);
		strbuf_release(&entry);
		return -1;

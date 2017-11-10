static void NORETURN die_verify_filename(const char *prefix,
					 const char *arg,
					 int diagnose_misspelt_rev)
{
	if (!diagnose_misspelt_rev)
		die(_("%s: no such path in the working tree.\n"
		      "Use 'git <command> -- <path>...' to specify paths that do not exist locally."),
		    arg);
	/*
	 * Saying "'(icase)foo' does not exist in the index" when the
	 * user gave us ":(icase)foo" is just stupid.  A magic pathspec
	 * begins with a colon and is followed by a non-alnum; do not
	 * let maybe_die_on_misspelt_object_name() even trigger.
	 */
	if (!(arg[0] == ':' && !isalnum(arg[1])))
		maybe_die_on_misspelt_object_name(arg, prefix);

	/* ... or fall back the most general message. */
	die(_("ambiguous argument '%s': unknown revision or path not in the working tree.\n"
	      "Use '--' to separate paths from revisions, like this:\n"
	      "'git <command> [<revision>...] -- [<file>...]'"), arg);

}
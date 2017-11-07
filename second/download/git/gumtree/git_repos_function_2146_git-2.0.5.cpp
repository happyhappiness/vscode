int error_resolve_conflict(const char *me)
{
	error("'%s' is not possible because you have unmerged files.", me);
	if (advice_resolve_conflict)
		/*
		 * Message used both when 'git commit' fails and when
		 * other commands doing a merge do.
		 */
		advise(_("Fix them up in the work tree,\n"
			 "and then use 'git add/rm <file>' as\n"
			 "appropriate to mark resolution and make a commit,\n"
			 "or use 'git commit -a'."));
	return -1;
}
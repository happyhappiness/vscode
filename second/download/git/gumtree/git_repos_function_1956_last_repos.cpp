int git_xmerge_config(const char *var, const char *value, void *cb)
{
	if (!strcmp(var, "merge.conflictstyle")) {
		if (!value)
			die("'%s' is not a boolean", var);
		if (!strcmp(value, "diff3"))
			git_xmerge_style = XDL_MERGE_DIFF3;
		else if (!strcmp(value, "merge"))
			git_xmerge_style = 0;
		else
			die("unknown style '%s' given for '%s'",
			    value, var);
		return 0;
	}
	return git_default_config(var, value, cb);
}
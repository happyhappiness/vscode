static void show_rename_copy(struct patch *p)
{
	const char *renamecopy = p->is_rename ? "rename" : "copy";
	const char *old, *new;

	/* Find common prefix */
	old = p->old_name;
	new = p->new_name;
	while (1) {
		const char *slash_old, *slash_new;
		slash_old = strchr(old, '/');
		slash_new = strchr(new, '/');
		if (!slash_old ||
		    !slash_new ||
		    slash_old - old != slash_new - new ||
		    memcmp(old, new, slash_new - new))
			break;
		old = slash_old + 1;
		new = slash_new + 1;
	}
	/* p->old_name thru old is the common prefix, and old and new
	 * through the end of names are renames
	 */
	if (old != p->old_name)
		printf(" %s %.*s{%s => %s} (%d%%)\n", renamecopy,
		       (int)(old - p->old_name), p->old_name,
		       old, new, p->score);
	else
		printf(" %s %s => %s (%d%%)\n", renamecopy,
		       p->old_name, p->new_name, p->score);
	show_mode_change(p, 0);
}
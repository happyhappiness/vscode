static BOOL is_below(struct file_struct *file, struct file_struct *subtree)
{
	return F_DEPTH(file) > F_DEPTH(subtree)
		&& (!implied_dirs_are_missing || f_name_has_prefix(file, subtree));
}
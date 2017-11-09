int f_name_has_prefix(const struct file_struct *f1, const struct file_struct *f2)
{
	found_prefix = 0;
	f_name_cmp(f1, f2);
	return found_prefix;
}
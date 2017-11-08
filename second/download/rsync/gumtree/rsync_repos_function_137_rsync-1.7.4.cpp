int file_compare(struct file_struct **f1,struct file_struct **f2)
{
	if (!(*f1)->basename && !(*f2)->basename) return 0;
	if (!(*f1)->basename) return -1;
	if (!(*f2)->basename) return 1;
	if ((*f1)->dirname == (*f2)->dirname)
		return strcmp((*f1)->basename, (*f2)->basename);
	return strcmp(f_name(*f1),f_name(*f2));
}
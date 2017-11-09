static int file_compare(const void *file1, const void *file2)
{
	return f_name_cmp(*(struct file_struct **)file1,
			  *(struct file_struct **)file2);
}
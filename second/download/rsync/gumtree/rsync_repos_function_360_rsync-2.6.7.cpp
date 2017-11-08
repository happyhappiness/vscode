static int file_compare(struct file_struct **file1, struct file_struct **file2)
{
	return f_name_cmp(*file1, *file2);
}
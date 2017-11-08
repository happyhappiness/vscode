void free_file(struct file_struct *file)
{
	if (!file)
		return;
	if (file->basename)
		free(file->basename);
	if (file->link)
		free(file->link);
	if (file->sum)
		free(file->sum);
	*file = null_file;
}
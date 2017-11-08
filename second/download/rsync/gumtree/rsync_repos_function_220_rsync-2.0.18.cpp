static void free_file(struct file_struct *file)
{
	if (!file) return;
	if (file->basename) free(file->basename);
	if (file->link) free(file->link);
	if (file->sum) free(file->sum);
	memset((char *)file, 0, sizeof(*file));
}
void unmake_file(struct file_struct *file)
{
	free(REQ_EXTRA(file, F_DEPTH(file)));
}
{
	int int_str_len;
	char char_str_len[4];
	char buff[256];
	struct file_struct *file;

	file = new(struct file_struct);
	if (!file)
		out_of_memory("read_batch_flist_info");
	memset((char *) file, 0, sizeof(*file));

	*fptr = file;


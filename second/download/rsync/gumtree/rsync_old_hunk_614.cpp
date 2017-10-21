
	file = (struct file_struct *) malloc(sizeof(*file));
	if (!file)
		out_of_memory("read_batch_flist_info");
	memset((char *) file, 0, sizeof(*file));

	(*fptr) = file;

	read_batch_flist_file((char *) &file->modtime, sizeof(time_t));
	read_batch_flist_file((char *) &file->length, sizeof(OFF_T));
	read_batch_flist_file((char *) &file->mode, sizeof(mode_t));
	read_batch_flist_file((char *) &file->inode, sizeof(INO64_T));
	read_batch_flist_file((char *) &file->dev, sizeof(DEV64_T));
	read_batch_flist_file((char *) &file->rdev, sizeof(DEV64_T));

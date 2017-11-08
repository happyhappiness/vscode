void read_batch_flist_info(struct file_struct **fptr)
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

	/*
	 * Keep these in sync with bytes_to_write assignment
	 * in write_batch_flist_info()
	 */
	read_batch_flist_file((char *) &file->modtime, sizeof(time_t));
	read_batch_flist_file((char *) &file->length, sizeof(OFF_T));
	read_batch_flist_file((char *) &file->mode, sizeof(mode_t));
	read_batch_flist_file((char *) &file->inode, sizeof(INO64_T));
	read_batch_flist_file((char *) &file->dev, sizeof(DEV64_T));
	read_batch_flist_file((char *) &file->rdev, sizeof(DEV64_T));
	read_batch_flist_file((char *) &file->uid, sizeof(uid_t));
	read_batch_flist_file((char *) &file->gid, sizeof(gid_t));
	read_batch_flist_file(char_str_len, sizeof(char_str_len));
	int_str_len = IVAL(char_str_len, 0);
	if (int_str_len > 0) {
		read_batch_flist_file(buff, int_str_len);
		buff[int_str_len] = '\0';
		file->basename = strdup(buff);
	} else {
		file->basename = NULL;
	}

	read_batch_flist_file(char_str_len, sizeof(char_str_len));
	int_str_len = IVAL(char_str_len, 0);
	if (int_str_len > 0) {
		read_batch_flist_file(buff, int_str_len);
		buff[int_str_len] = '\0';
		file[0].dirname = strdup(buff);
	} else {
		file[0].dirname = NULL;
	}

	read_batch_flist_file(char_str_len, sizeof(char_str_len));
	int_str_len = IVAL(char_str_len, 0);
	if (int_str_len > 0) {
		read_batch_flist_file(buff, int_str_len);
		buff[int_str_len] = '\0';
		file[0].basedir = strdup(buff);
	} else {
		file[0].basedir = NULL;
	}

	read_batch_flist_file(char_str_len, sizeof(char_str_len));
	int_str_len = IVAL(char_str_len, 0);
	if (int_str_len > 0) {
		read_batch_flist_file(buff, int_str_len);
		buff[int_str_len] = '\0';
		file[0].link = strdup(buff);
	} else {
		file[0].link = NULL;
	}

	read_batch_flist_file(char_str_len, sizeof(char_str_len));
	int_str_len = IVAL(char_str_len, 0);
	if (int_str_len > 0) {
		read_batch_flist_file(buff, int_str_len);
		buff[int_str_len] = '\0';
		file[0].sum = strdup(buff);
	} else {
		file[0].sum = NULL;
	}
}
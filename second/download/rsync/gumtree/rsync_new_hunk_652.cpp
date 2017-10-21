			file->inode = read_longint(f);
		}
	}
#endif

	if (always_checksum) {
		file->sum = new_array(char, MD4_SUM_LENGTH);
		if (!file->sum)
			out_of_memory("md4 sum");
		if (remote_version < 21) {
			read_buf(f, file->sum, 2);
		} else {
			read_buf(f, file->sum, MD4_SUM_LENGTH);

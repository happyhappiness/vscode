{
		archive_read_extract_set_skip_file(a, st.st_dev, st.st_ino);
		mine->use_lseek = 1;
	}
(i = 0; i < namelen; i++) {
		if (p[i + H1_FILE_NAME_OFFSET] == 0xff)
			goto invalid;/* Invalid filename. */
	}
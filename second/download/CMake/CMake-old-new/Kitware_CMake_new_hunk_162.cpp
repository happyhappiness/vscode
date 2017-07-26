		if ((file->utf16be_name = malloc(name_len)) == NULL) {
			archive_set_error(&a->archive, ENOMEM,
			    "No memory for file name");
			goto fail;
		}
		memcpy(file->utf16be_name, p, name_len);
		file->utf16be_bytes = name_len;

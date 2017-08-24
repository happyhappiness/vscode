(numFolders > 1) {
		struct file *file = zip->file_list.first;
		for (;file != NULL; file = file->next) {
			if (file->size == 0)
				break;
			r = enc_uint64(a, file->size);
			if (r < 0)
				return (r);
		}

	} else {
		/* Write UnPackSize. */
		r = enc_uint64(a, unpack_size);
		if (r < 0)
			return (r);
	}
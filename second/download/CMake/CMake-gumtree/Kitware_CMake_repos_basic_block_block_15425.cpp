{
		/*
		 * Make NumUnPackStream.
		 */
		r = enc_uint64(a, kNumUnPackStream);
		if (r < 0)
			return (r);

		/* Write numUnpackStreams */
		r = enc_uint64(a, zip->total_number_nonempty_entry);
		if (r < 0)
			return (r);

		/*
		 * Make kSize.
		 */
		r = enc_uint64(a, kSize);
		if (r < 0)
			return (r);
		file = zip->file_list.first;
		for (;file != NULL; file = file->next) {
			if (file->next == NULL ||
			    file->next->size == 0)
				break;
			r = enc_uint64(a, file->size);
			if (r < 0)
				return (r);
		}
	}
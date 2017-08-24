{
		/*
		 * Entry is archive filename table, inform that we should
		 * collect strtab in next _data call.
		 */
		ar->is_strtab = 1;
		buff[AR_name_offset] = buff[AR_name_offset + 1] = '/';
		/*
		 * For archive string table, only ar_size field should
		 * be set.
		 */
		goto size;
	}
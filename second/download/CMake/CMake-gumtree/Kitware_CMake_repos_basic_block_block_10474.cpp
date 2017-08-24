{
		/*
		 * If there is remaining data which is saved by
		 * previous calling, use it first.
		 */
		if (ensure_in_buff_size(self, uudecode,
		    avail_in + uudecode->in_cnt) != ARCHIVE_OK)
			return (ARCHIVE_FATAL);
		memcpy(uudecode->in_buff + uudecode->in_cnt,
		    d, avail_in);
		d = uudecode->in_buff;
		avail_in += uudecode->in_cnt;
		uudecode->in_cnt = 0;
	}
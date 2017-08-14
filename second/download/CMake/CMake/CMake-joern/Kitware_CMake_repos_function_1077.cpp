static int
ensure_in_buff_size(struct archive_read_filter *self,
    struct uudecode *uudecode, size_t size)
{

	if (size > uudecode->in_allocated) {
		unsigned char *ptr;
		size_t newsize;

		/*
		 * Calculate a new buffer size for in_buff.
		 * Increase its value until it has enough size we need.
		 */
		newsize = uudecode->in_allocated;
		do {
			if (newsize < IN_BUFF_SIZE*32)
				newsize <<= 1;
			else
				newsize += IN_BUFF_SIZE;
		} while (size > newsize);
		/* Allocate the new buffer. */
		ptr = malloc(newsize);
		if (ptr == NULL) {
			free(ptr);
			archive_set_error(&self->archive->archive,
			    ENOMEM,
    			    "Can't allocate data for uudecode");
			return (ARCHIVE_FATAL);
		}
		/* Move the remaining data in in_buff into the new buffer. */
		if (uudecode->in_cnt)
			memmove(ptr, uudecode->in_buff, uudecode->in_cnt);
		/* Replace in_buff with the new buffer. */
		free(uudecode->in_buff);
		uudecode->in_buff = ptr;
		uudecode->in_allocated = newsize;
	}
	return (ARCHIVE_OK);
}
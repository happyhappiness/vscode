static int
drive_compressor(struct archive_write_filter *f,
    struct private_data *data, int finishing)
{
	int ret;

	for (;;) {
		if (data->stream.avail_out == 0) {
			ret = __archive_write_filter(f->next_filter,
			    data->compressed,
			    data->compressed_buffer_size);
			if (ret != ARCHIVE_OK) {
				/* TODO: Handle this write failure */
				return (ARCHIVE_FATAL);
			}
			data->stream.next_out = data->compressed;
			data->stream.avail_out = data->compressed_buffer_size;
		}

		/* If there's nothing to do, we're done. */
		if (!finishing && data->stream.avail_in == 0)
			return (ARCHIVE_OK);

		ret = BZ2_bzCompress(&(data->stream),
		    finishing ? BZ_FINISH : BZ_RUN);

		switch (ret) {
		case BZ_RUN_OK:
			/* In non-finishing case, did compressor
			 * consume everything? */
			if (!finishing && data->stream.avail_in == 0)
				return (ARCHIVE_OK);
			break;
		case BZ_FINISH_OK:  /* Finishing: There's more work to do */
			break;
		case BZ_STREAM_END: /* Finishing: all done */
			/* Only occurs in finishing case */
			return (ARCHIVE_OK);
		default:
			/* Any other return value indicates an error */
			archive_set_error(f->archive,
			    ARCHIVE_ERRNO_PROGRAMMER,
			    "Bzip2 compression failed;"
			    " BZ2_bzCompress() returned %d",
			    ret);
			return (ARCHIVE_FATAL);
		}
	}
}
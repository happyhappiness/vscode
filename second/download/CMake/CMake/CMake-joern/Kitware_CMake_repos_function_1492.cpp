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
			if (ret != ARCHIVE_OK)
				return (ARCHIVE_FATAL);
			data->stream.next_out = data->compressed;
			data->stream.avail_out =
			    (uInt)data->compressed_buffer_size;
		}

		/* If there's nothing to do, we're done. */
		if (!finishing && data->stream.avail_in == 0)
			return (ARCHIVE_OK);

		ret = deflate(&(data->stream),
		    finishing ? Z_FINISH : Z_NO_FLUSH );

		switch (ret) {
		case Z_OK:
			/* In non-finishing case, check if compressor
			 * consumed everything */
			if (!finishing && data->stream.avail_in == 0)
				return (ARCHIVE_OK);
			/* In finishing case, this return always means
			 * there's more work */
			break;
		case Z_STREAM_END:
			/* This return can only occur in finishing case. */
			return (ARCHIVE_OK);
		default:
			/* Any other return value indicates an error. */
			archive_set_error(f->archive, ARCHIVE_ERRNO_MISC,
			    "GZip compression failed:"
			    " deflate() call returned status %d",
			    ret);
			return (ARCHIVE_FATAL);
		}
	}
}
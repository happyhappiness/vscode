int git_inflate(git_zstream *strm, int flush)
{
	int status;

	for (;;) {
		zlib_pre_call(strm);
		/* Never say Z_FINISH unless we are feeding everything */
		status = inflate(&strm->z,
				 (strm->z.avail_in != strm->avail_in)
				 ? 0 : flush);
		if (status == Z_MEM_ERROR)
			die("inflate: out of memory");
		zlib_post_call(strm);

		/*
		 * Let zlib work another round, while we can still
		 * make progress.
		 */
		if ((strm->avail_out && !strm->z.avail_out) &&
		    (status == Z_OK || status == Z_BUF_ERROR))
			continue;
		break;
	}

	switch (status) {
	/* Z_BUF_ERROR: normal, needs more space in the output buffer */
	case Z_BUF_ERROR:
	case Z_OK:
	case Z_STREAM_END:
		return status;
	default:
		break;
	}
	error("inflate: %s (%s)", zerr_to_string(status),
	      strm->z.msg ? strm->z.msg : "no message");
	return status;
}
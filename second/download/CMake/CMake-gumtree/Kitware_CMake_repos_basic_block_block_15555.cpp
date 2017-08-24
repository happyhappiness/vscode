{
	bz_stream *strm;
	int r;

	strm = (bz_stream *)lastrm->real_stream;
	r = BZ2_bzCompressEnd(strm);
	free(strm);
	lastrm->real_stream = NULL;
	lastrm->valid = 0;
	if (r != BZ_OK) {
		archive_set_error(a, ARCHIVE_ERRNO_MISC,
		    "Failed to clean up compressor");
		return (ARCHIVE_FATAL);
	}
	return (ARCHIVE_OK);
}
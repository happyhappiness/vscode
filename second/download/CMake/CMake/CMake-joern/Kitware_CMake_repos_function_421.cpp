static int
compression_end_deflate(struct archive *a, struct la_zstream *lastrm)
{
	z_stream *strm;
	int r;

	strm = (z_stream *)lastrm->real_stream;
	r = deflateEnd(strm);
	free(strm);
	lastrm->real_stream = NULL;
	lastrm->valid = 0;
	if (r != Z_OK) {
		archive_set_error(a, ARCHIVE_ERRNO_MISC,
		    "Failed to clean up compressor");
		return (ARCHIVE_FATAL);
	}
	return (ARCHIVE_OK);
}
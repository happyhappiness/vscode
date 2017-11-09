void git_inflate_init_gzip_only(git_zstream *strm)
{
	/*
	 * Use default 15 bits, +16 is to accept only gzip and to
	 * yield Z_DATA_ERROR when fed zlib format.
	 */
	const int windowBits = 15 + 16;
	int status;

	zlib_pre_call(strm);
	status = inflateInit2(&strm->z, windowBits);
	zlib_post_call(strm);
	if (status == Z_OK)
		return;
	die("inflateInit2: %s (%s)", zerr_to_string(status),
	    strm->z.msg ? strm->z.msg : "no message");
}
static void do_git_deflate_init(git_zstream *strm, int level, int windowBits)
{
	int status;

	memset(strm, 0, sizeof(*strm));
	zlib_pre_call(strm);
	status = deflateInit2(&strm->z, level,
				  Z_DEFLATED, windowBits,
				  8, Z_DEFAULT_STRATEGY);
	zlib_post_call(strm);
	if (status == Z_OK)
		return;
	die("deflateInit2: %s (%s)", zerr_to_string(status),
	    strm->z.msg ? strm->z.msg : "no message");
}
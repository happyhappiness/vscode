void git_inflate_init(git_zstream *strm)
{
	int status;

	zlib_pre_call(strm);
	status = inflateInit(&strm->z);
	zlib_post_call(strm);
	if (status == Z_OK)
		return;
	die("inflateInit: %s (%s)", zerr_to_string(status),
	    strm->z.msg ? strm->z.msg : "no message");
}
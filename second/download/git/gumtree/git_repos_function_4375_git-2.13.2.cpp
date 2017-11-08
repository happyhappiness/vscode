void git_inflate_end(git_zstream *strm)
{
	int status;

	zlib_pre_call(strm);
	status = inflateEnd(&strm->z);
	zlib_post_call(strm);
	if (status == Z_OK)
		return;
	error("inflateEnd: %s (%s)", zerr_to_string(status),
	      strm->z.msg ? strm->z.msg : "no message");
}
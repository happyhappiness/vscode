}

void git_deflate_init(git_zstream *strm, int level)
{
	int status;

	memset(strm, 0, sizeof(*strm));
	zlib_pre_call(strm);
	status = deflateInit(&strm->z, level);
	zlib_post_call(strm);
	if (status == Z_OK)
		return;
	die("deflateInit: %s (%s)", zerr_to_string(status),

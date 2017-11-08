int git_deflate_abort(git_zstream *strm)
{
	int status;

	zlib_pre_call(strm);
	status = deflateEnd(&strm->z);
	zlib_post_call(strm);
	return status;
}
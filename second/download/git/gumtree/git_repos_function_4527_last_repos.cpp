void git_deflate_end(git_zstream *strm)
{
	int status = git_deflate_abort(strm);

	if (status == Z_OK)
		return;
	error("deflateEnd: %s (%s)", zerr_to_string(status),
	      strm->z.msg ? strm->z.msg : "no message");
}
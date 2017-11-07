void git_deflate_init_gzip(git_zstream *strm, int level)
{
	/*
	 * Use default 15 bits, +16 is to generate gzip header/trailer
	 * instead of the zlib wrapper.
	 */
	do_git_deflate_init(strm, level, 15 + 16);
}
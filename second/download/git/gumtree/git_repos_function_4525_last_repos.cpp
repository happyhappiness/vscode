void git_deflate_init_raw(git_zstream *strm, int level)
{
	/*
	 * Use default 15 bits, negate the value to get raw compressed
	 * data without zlib header and trailer.
	 */
	do_git_deflate_init(strm, level, -15);
}
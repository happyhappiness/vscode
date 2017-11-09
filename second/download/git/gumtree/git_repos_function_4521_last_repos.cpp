unsigned long git_deflate_bound(git_zstream *strm, unsigned long size)
{
	return deflateBound(&strm->z, size);
}
static int write_index_ext_header(git_SHA_CTX *context, int fd,
				  unsigned int ext, unsigned int sz)
{
	ext = htonl(ext);
	sz = htonl(sz);
	return ((ce_write(context, fd, &ext, 4) < 0) ||
		(ce_write(context, fd, &sz, 4) < 0)) ? -1 : 0;
}
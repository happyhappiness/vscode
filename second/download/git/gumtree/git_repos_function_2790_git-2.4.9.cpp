uint32_t crc32_end(struct sha1file *f)
{
	f->do_crc = 0;
	return f->crc32;
}
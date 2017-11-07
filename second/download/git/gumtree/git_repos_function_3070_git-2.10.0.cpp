void crc32_begin(struct sha1file *f)
{
	f->crc32 = crc32(0, NULL, 0);
	f->do_crc = 1;
}
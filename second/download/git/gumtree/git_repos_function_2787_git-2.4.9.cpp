void sha1file_checkpoint(struct sha1file *f, struct sha1file_checkpoint *checkpoint)
{
	sha1flush(f);
	checkpoint->offset = f->total;
	checkpoint->ctx = f->ctx;
}
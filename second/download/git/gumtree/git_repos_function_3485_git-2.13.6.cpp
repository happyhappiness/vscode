void sha1flush(struct sha1file *f)
{
	unsigned offset = f->offset;

	if (offset) {
		git_SHA1_Update(&f->ctx, f->buffer, offset);
		flush(f, f->buffer, offset);
		f->offset = 0;
	}
}
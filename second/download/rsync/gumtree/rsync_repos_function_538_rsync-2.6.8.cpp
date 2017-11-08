void mdfour(unsigned char *out, unsigned char *in, int n)
{
	struct mdfour md;
	mdfour_begin(&md);
	mdfour_update(&md, in, n);
	mdfour_result(&md, out);
}
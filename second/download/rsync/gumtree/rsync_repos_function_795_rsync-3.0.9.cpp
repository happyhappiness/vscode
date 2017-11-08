void mdfour(uchar digest[MD4_DIGEST_LEN], uchar *in, int length)
{
	md_context md;
	mdfour_begin(&md);
	mdfour_update(&md, in, length);
	mdfour_result(&md, digest);
}
void mdfour_result(md_context *md, uchar digest[MD4_DIGEST_LEN])
{
	m = md;

	copy4(digest, m->A);
	copy4(digest+4, m->B);
	copy4(digest+8, m->C);
	copy4(digest+12, m->D);
}
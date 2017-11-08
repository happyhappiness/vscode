void mdfour_result(struct mdfour *md, unsigned char *out)
{
	m = md;

	copy4(out, m->A);
	copy4(out+4, m->B);
	copy4(out+8, m->C);
	copy4(out+12, m->D);
}
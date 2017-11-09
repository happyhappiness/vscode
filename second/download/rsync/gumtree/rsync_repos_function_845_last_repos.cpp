void mdfour_begin(md_context *md)
{
	md->A = 0x67452301;
	md->B = 0xefcdab89;
	md->C = 0x98badcfe;
	md->D = 0x10325476;
	md->totalN = 0;
	md->totalN2 = 0;
}
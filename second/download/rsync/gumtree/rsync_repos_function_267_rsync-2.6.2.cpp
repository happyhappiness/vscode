void sum_init(void)
{
	char s[4];
	mdfour_begin(&md);
	sumresidue=0;
	SIVAL(s,0,checksum_seed);
	sum_update(s,4);
}
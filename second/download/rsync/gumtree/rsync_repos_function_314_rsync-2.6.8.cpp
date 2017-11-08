void sum_init(int seed)
{
	char s[4];
	mdfour_begin(&md);
	sumresidue = 0;
	SIVAL(s, 0, seed);
	sum_update(s, 4);
}
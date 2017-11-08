void sum_init(int seed)
{
	char s[4];

	if (protocol_version >= 30)
		md5_begin(&md);
	else {
		mdfour_begin(&md);
		sumresidue = 0;
		SIVAL(s, 0, seed);
		sum_update(s, 4);
	}
}
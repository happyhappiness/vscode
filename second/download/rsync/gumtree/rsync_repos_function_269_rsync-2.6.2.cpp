void sum_end(char *sum)
{
	if (sumresidue || protocol_version >= 27) {
		mdfour_update(&md, (uchar *)sumrbuf, sumresidue);
	}

	mdfour_result(&md, (uchar *)sum);
}
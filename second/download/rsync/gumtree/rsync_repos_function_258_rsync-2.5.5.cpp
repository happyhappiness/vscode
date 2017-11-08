void sum_end(char *sum)
{
	if (sumresidue) {
		mdfour_update(&md, (uchar *)sumrbuf, sumresidue);
	}

	mdfour_result(&md, (uchar *)sum);
}
int sum_end(char *sum)
{
	if (protocol_version >= 30) {
		md5_result(&md, (uchar *)sum);
		return MD5_DIGEST_LEN;
	}

	if (sumresidue || protocol_version >= 27)
		mdfour_update(&md, (uchar *)md.buffer, sumresidue);

	mdfour_result(&md, (uchar *)sum);

	return MD4_DIGEST_LEN;
}
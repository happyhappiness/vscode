void sum_update(char *p, int32 len)
{
	if (len + sumresidue < CSUM_CHUNK) {
		memcpy(sumrbuf + sumresidue, p, len);
		sumresidue += len;
		return;
	}

	if (sumresidue) {
		int32 i = CSUM_CHUNK - sumresidue;
		memcpy(sumrbuf + sumresidue, p, i);
		mdfour_update(&md, (uchar *)sumrbuf, CSUM_CHUNK);
		len -= i;
		p += i;
	}

	while (len >= CSUM_CHUNK) {
		mdfour_update(&md, (uchar *)p, CSUM_CHUNK);
		len -= CSUM_CHUNK;
		p += CSUM_CHUNK;
	}

	sumresidue = len;
	if (sumresidue)
		memcpy(sumrbuf, p, sumresidue);
}
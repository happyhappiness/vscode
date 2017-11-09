void sum_update(const char *p, int32 len)
{
	if (protocol_version >= 30) {
		md5_update(&md, (uchar *)p, len);
		return;
	}

	if (len + sumresidue < CSUM_CHUNK) {
		memcpy(md.buffer + sumresidue, p, len);
		sumresidue += len;
		return;
	}

	if (sumresidue) {
		int32 i = CSUM_CHUNK - sumresidue;
		memcpy(md.buffer + sumresidue, p, i);
		mdfour_update(&md, (uchar *)md.buffer, CSUM_CHUNK);
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
		memcpy(md.buffer, p, sumresidue);
}
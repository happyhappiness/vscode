void sum_update(char *p, int len)
{
	int i;
	if (len + sumresidue < CSUM_CHUNK) {
		memcpy(sumrbuf+sumresidue, p, len);
		sumresidue += len;
		return;
	}

	if (sumresidue) {
		i = MIN(CSUM_CHUNK-sumresidue,len);
		memcpy(sumrbuf+sumresidue,p,i);
		mdfour_update(&md, (uchar *)sumrbuf, (i+sumresidue));
		len -= i;
		p += i;
	}

	for(i = 0; i + CSUM_CHUNK <= len; i += CSUM_CHUNK) {
		memcpy(sumrbuf,p+i,CSUM_CHUNK);
		mdfour_update(&md, (uchar *)sumrbuf, CSUM_CHUNK);
	}

	if (len - i > 0) {
		sumresidue = len-i;
		memcpy(sumrbuf,p+i,sumresidue);
	} else {
		sumresidue = 0;    
	}
}
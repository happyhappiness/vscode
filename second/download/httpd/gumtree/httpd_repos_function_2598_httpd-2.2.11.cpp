static int
seepair(pag, n, key, siz)
char *pag;
register int n;
register char *key;
register int siz;
{
	register int i;
	register int off = PBLKSIZ;
	register short *ino = (short *) pag;

	for (i = 1; i < n; i += 2) {
		if (siz == off - ino[i] &&
		    memcmp(key, pag + ino[i], siz) == 0)
			return i;
		off = ino[i + 1];
	}
	return 0;
}
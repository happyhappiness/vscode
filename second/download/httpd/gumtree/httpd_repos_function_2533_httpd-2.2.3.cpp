int
fitpair(pag, need)
char *pag;
int need;
{
	register int n;
	register int off;
	register int avail;
	register short *ino = (short *) pag;

	off = ((n = ino[0]) > 0) ? ino[n] : PBLKSIZ;
	avail = off - (n + 1) * sizeof(short);
	need += 2 * sizeof(short);

	debug(("avail %d need %d\n", avail, need));

	return need <= avail;
}
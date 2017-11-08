int
chkpage(pag)
char *pag;
{
	register int n;
	register int off;
	register short *ino = (short *) pag;

	if ((n = ino[0]) < 0 || n > PBLKSIZ / sizeof(short))
		return 0;

	if (n > 0) {
		off = PBLKSIZ;
		for (ino++; n > 0; ino += 2) {
			if (ino[0] > off || ino[1] > off ||
			    ino[1] > ino[0])
				return 0;
			off = ino[1];
			n -= 2;
		}
	}
	return 1;
}
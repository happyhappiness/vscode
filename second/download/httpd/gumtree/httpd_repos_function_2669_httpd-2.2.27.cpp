int
delpair(pag, key)
char *pag;
apr_sdbm_datum_t key;
{
	register int n;
	register int i;
	register short *ino = (short *) pag;

	if ((n = ino[0]) == 0)
		return 0;

	if ((i = seepair(pag, n, key.dptr, key.dsize)) == 0)
		return 0;
/*
 * found the key. if it is the last entry
 * [i.e. i == n - 1] we just adjust the entry count.
 * hard case: move all data down onto the deleted pair,
 * shift offsets onto deleted offsets, and adjust them.
 * [note: 0 < i < n]
 */
	if (i < n - 1) {
		register int m;
		register char *dst = pag + (i == 1 ? PBLKSIZ : ino[i - 1]);
		register char *src = pag + ino[i + 1];
		register short zoo = (short) (dst - src);

		debug(("free-up %d ", zoo));
/*
 * shift data/keys down
 */
		m = ino[i + 1] - ino[n];

#undef DUFF	/* just use memmove. it should be plenty fast. */
#ifdef DUFF
#define MOVB 	*--dst = *--src

		if (m > 0) {
			register int loop = (m + 8 - 1) >> 3;

			switch (m & (8 - 1)) {
			case 0:	do {
				MOVB;	case 7:	MOVB;
			case 6:	MOVB;	case 5:	MOVB;
			case 4:	MOVB;	case 3:	MOVB;
			case 2:	MOVB;	case 1:	MOVB;
				} while (--loop);
			}
		}
#else
		dst -= m;
		src -= m;
		memmove(dst, src, m);
#endif

/*
 * adjust offset index up
 */
		while (i < n - 1) {
			ino[i] = ino[i + 2] + zoo;
			i++;
		}
	}
	ino[0] -= 2;
	return 1;
}
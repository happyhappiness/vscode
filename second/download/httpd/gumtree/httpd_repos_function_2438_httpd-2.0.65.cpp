void
splpage(pag, new, sbit)
char *pag;
char *new;
long sbit;
{
	apr_sdbm_datum_t key;
	apr_sdbm_datum_t val;

	register int n;
	register int off = PBLKSIZ;
	char cur[PBLKSIZ];
	register short *ino = (short *) cur;

	(void) memcpy(cur, pag, PBLKSIZ);
	(void) memset(pag, 0, PBLKSIZ);
	(void) memset(new, 0, PBLKSIZ);

	n = ino[0];
	for (ino++; n > 0; ino += 2) {
		key.dptr = cur + ino[0]; 
		key.dsize = off - ino[0];
		val.dptr = cur + ino[1];
		val.dsize = ino[0] - ino[1];
/*
 * select the page pointer (by looking at sbit) and insert
 */
		(void) putpair((exhash(key) & sbit) ? new : pag, key, val);

		off = ino[1];
		n -= 2;
	}

	debug(("%d split %d/%d\n", ((short *) cur)[0] / 2, 
	       ((short *) new)[0] / 2,
	       ((short *) pag)[0] / 2));
}
void
putpair(pag, key, val)
char *pag;
apr_sdbm_datum_t key;
apr_sdbm_datum_t val;
{
	register int n;
	register int off;
	register short *ino = (short *) pag;

	off = ((n = ino[0]) > 0) ? ino[n] : PBLKSIZ;
/*
 * enter the key first
 */
	off -= key.dsize;
	(void) memcpy(pag + off, key.dptr, key.dsize);
	ino[n + 1] = off;
/*
 * now the data
 */
	off -= val.dsize;
	(void) memcpy(pag + off, val.dptr, val.dsize);
	ino[n + 2] = off;
/*
 * adjust item count
 */
	ino[0] += 2;
}
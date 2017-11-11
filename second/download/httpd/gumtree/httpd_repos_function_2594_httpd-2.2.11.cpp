apr_sdbm_datum_t
getpair(pag, key)
char *pag;
apr_sdbm_datum_t key;
{
	register int i;
	register int n;
	apr_sdbm_datum_t val;
	register short *ino = (short *) pag;

	if ((n = ino[0]) == 0)
		return sdbm_nullitem;

	if ((i = seepair(pag, n, key.dptr, key.dsize)) == 0)
		return sdbm_nullitem;

	val.dptr = pag + ino[i + 1];
	val.dsize = ino[i] - ino[i + 1];
	return val;
}
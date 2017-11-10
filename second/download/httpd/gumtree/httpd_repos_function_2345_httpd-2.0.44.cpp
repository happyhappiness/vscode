apr_sdbm_datum_t
getnkey(pag, num)
char *pag;
int num;
{
	apr_sdbm_datum_t key;
	register int off;
	register short *ino = (short *) pag;

	num = num * 2 - 1;
	if (ino[0] == 0 || num > ino[0])
		return sdbm_nullitem;

	off = (num > 1) ? ino[num - 1] : PBLKSIZ;

	key.dptr = pag + ino[num];
	key.dsize = off - ino[num];

	return key;
}
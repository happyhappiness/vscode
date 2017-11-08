int
duppair(pag, key)
char *pag;
apr_sdbm_datum_t key;
{
	register short *ino = (short *) pag;
	return ino[0] > 0 && seepair(pag, ino[0], key.dptr, key.dsize) > 0;
}
local int inflate_addhistory(s, z)
inflate_blocks_statef *s;
z_stream *z;
{
    uLong b;              /* bit buffer */  /* NOT USED HERE */
    uInt k;               /* bits in bit buffer */ /* NOT USED HERE */
    uInt t;               /* temporary storage */
    Bytef *p;             /* input data pointer */
    uInt n;               /* bytes available there */
    Bytef *q;             /* output window write pointer */
    uInt m;               /* bytes to end of window or read pointer */

    if (s->read != s->write)
	return Z_STREAM_ERROR;
    if (s->mode != TYPE)
	return Z_DATA_ERROR;

    /* we're ready to rock */
    LOAD
    /* while there is input ready, copy to output buffer, moving
     * pointers as needed.
     */
    while (n) {
	t = n;  /* how many to do */
	/* is there room until end of buffer? */
	if (t > m) t = m;
	/* update check information */
	if (s->checkfn != Z_NULL)
	    s->check = (*s->checkfn)(s->check, q, t);
	zmemcpy(q, p, t);
	q += t;
	p += t;
	n -= t;
	z->total_out += t;
	s->read = q;    /* drag read pointer forward */
/*      ZWRAP  */ 	/* expand ZWRAP macro by hand to handle s->read */
	if (q == s->end) {
	    s->read = q = s->window;
	    m = WAVAIL;
	}
    }
    UPDATE
    return Z_OK;
}
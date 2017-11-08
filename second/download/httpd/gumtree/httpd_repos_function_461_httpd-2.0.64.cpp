static int zmagic(request_rec *r, unsigned char *buf, apr_size_t nbytes)
{
    unsigned char *newbuf;
    int newsize;
    int i;

    for (i = 0; i < ncompr; i++) {
	if (nbytes < compr[i].maglen)
	    continue;
	if (memcmp(buf, compr[i].magic, compr[i].maglen) == 0)
	    break;
    }

    if (i == ncompr)
	return 0;

    if ((newsize = uncompress(r, i, &newbuf, nbytes)) > 0) {
	if (tryit(r, newbuf, newsize, 0) != OK) {
            return 0;
        }

	/* set encoding type in the request record */
	r->content_encoding = compr[i].encoding;
    }
    return 1;
}
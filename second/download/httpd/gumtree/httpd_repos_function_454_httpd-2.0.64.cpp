static int softmagic(request_rec *r, unsigned char *buf, apr_size_t nbytes)
{
    if (match(r, buf, nbytes))
	return 1;

    return 0;
}
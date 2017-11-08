static void tryit(request_rec *r, unsigned char *buf, apr_size_t nb, int checkzmagic)
{
    /*
     * Try compression stuff
     */
	if (checkzmagic == 1) {  
			if (zmagic(r, buf, nb) == 1)
			return;
	}

    /*
     * try tests in /etc/magic (or surrogate magic file)
     */
    if (softmagic(r, buf, nb) == 1)
	return;

    /*
     * try known keywords, check for ascii-ness too.
     */
    if (ascmagic(r, buf, nb) == 1)
	return;

    /*
     * abandon hope, all ye who remain here
     */
    magic_rsl_puts(r, MIME_BINARY_UNKNOWN);
}
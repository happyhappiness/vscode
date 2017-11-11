static dav_error * dav_fs_remove_locknull_member(apr_pool_t *p,
                                                 const char *filename,
						 dav_buffer *pbuf)
{
    dav_error *err;
    apr_size_t len;
    apr_size_t scanlen;
    char *scan;
    const char *scanend;
    char *dirpath = apr_pstrdup(p, filename);
    char *fname = strrchr(dirpath, '/');
    int dirty = 0;

    if (fname != NULL)
	*fname++ = '\0';
    else
	fname = dirpath;
    len = strlen(fname) + 1;

    if ((err = dav_fs_load_locknull_list(p, dirpath, pbuf)) != NULL) {
	/* ### add a higher level description? */
	return err;
    }

    for (scan = pbuf->buf, scanend = scan + pbuf->cur_len;
	 scan < scanend;
	 scan += scanlen) {
	scanlen = strlen(scan) + 1;
	if (len == scanlen && memcmp(fname, scan, scanlen) == 0) {
	    pbuf->cur_len -= scanlen;
	    memmove(scan, scan + scanlen, scanend - (scan + scanlen));
	    dirty = 1;
	    break;
	}
    }

    if (dirty) {
	if ((err = dav_fs_save_locknull_list(p, dirpath, pbuf)) != NULL) {
	    /* ### add a higher level description? */
	    return err;
	}
    }

    return NULL;
}
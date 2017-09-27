/* ------------------------------------------------------- */

/* read data to POST from file, save contents and length */

static int open_postfile(const char *pfile)
{
    apr_file_t *postfd = NULL;
    apr_finfo_t finfo;
    apr_fileperms_t mode = APR_OS_DEFAULT;
    apr_size_t length;
    apr_status_t rv;
    char errmsg[120];

    rv = apr_file_open(&postfd, pfile, APR_READ, mode, cntxt);
    if (rv != APR_SUCCESS) {
	printf("Invalid postfile name (%s): %s\n", pfile,
	       apr_strerror(rv, errmsg, sizeof errmsg));
	return rv;
    }

    apr_file_info_get(&finfo, APR_FINFO_NORM, postfd);
    postlen = (apr_size_t)finfo.size;
    postdata = (char *) malloc(postlen);
    if (!postdata) {
	printf("Can\'t alloc postfile buffer\n");
	return APR_ENOMEM;
    }
    length = postlen;
    rv = apr_file_read(postfd, postdata, &length);
    if (rv != APR_SUCCESS) {
	printf("error reading postfile: %s\n",
	       apr_strerror(rv, errmsg, sizeof errmsg));
	return rv;
    }
    if (length != postlen) {
	printf("error reading postfile: read only %"
	       APR_SIZE_T_FMT " bytes",
	       length);
	return APR_EINVAL;
    }
    apr_file_close(postfd);
    return 0;
}

/* ------------------------------------------------------- */


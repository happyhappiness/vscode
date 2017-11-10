static void create_testfile(apr_pool_t *p, const char *fname)
{
    apr_file_t *f = NULL;
    apr_status_t rv;
    char buf[120];
    int i;
    apr_finfo_t finfo;

    printf("Creating a test file...\n");
    rv = apr_file_open(&f, fname, 
                 APR_FOPEN_CREATE | APR_FOPEN_WRITE | APR_FOPEN_TRUNCATE | APR_FOPEN_BUFFERED,
                 APR_UREAD | APR_UWRITE, p);
    if (rv) {
        fprintf(stderr, "apr_file_open()->%d/%s\n",
                rv, apr_strerror(rv, buf, sizeof buf));
        exit(1);
    }
    
    buf[0] = FILE_DATA_CHAR;
    buf[1] = '\0';
    for (i = 0; i < FILE_LENGTH; i++) {
        /* exercise apr_file_putc() and apr_file_puts() on buffered files */
        if ((i % 2) == 0) {
            rv = apr_file_putc(buf[0], f);
            if (rv) {
                fprintf(stderr, "apr_file_putc()->%d/%s\n",
                        rv, apr_strerror(rv, buf, sizeof buf));
                exit(1);
            }
        }
        else {
            rv = apr_file_puts(buf, f);
            if (rv) {
                fprintf(stderr, "apr_file_puts()->%d/%s\n",
                        rv, apr_strerror(rv, buf, sizeof buf));
                exit(1);
            }
        }
    }

    rv = apr_file_close(f);
    if (rv) {
        fprintf(stderr, "apr_file_close()->%d/%s\n",
                rv, apr_strerror(rv, buf, sizeof buf));
        exit(1);
    }

    rv = apr_stat(&finfo, fname, APR_FINFO_NORM, p);
    if (rv != APR_SUCCESS && ! APR_STATUS_IS_INCOMPLETE(rv)) {
        fprintf(stderr, "apr_stat()->%d/%s\n",
                rv, apr_strerror(rv, buf, sizeof buf));
        exit(1);
    }

    if (finfo.size != FILE_LENGTH) {
        fprintf(stderr, 
                "test file %s should be %ld-bytes long\n"
                "instead it is %ld-bytes long\n",
                fname,
                (long int)FILE_LENGTH,
                (long int)finfo.size);
        exit(1);
    }
}
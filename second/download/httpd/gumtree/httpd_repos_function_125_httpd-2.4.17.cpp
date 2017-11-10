int main(int argc, const char * const argv[])
{
    apr_file_t * outfile;
    apr_file_t * infile;
    apr_getopt_t * o;
    apr_pool_t * pool;
    apr_pool_t *pline;
    apr_status_t status;
    const char * arg;
    char * stats = NULL;
    char * inbuffer;
    char * outbuffer;
    char * line;
    int doublelookups = 0;

    if (apr_app_initialize(&argc, &argv, NULL) != APR_SUCCESS) {
        return 1;
    }
    atexit(apr_terminate);

    if (argc) {
        shortname = apr_filepath_name_get(argv[0]);
    }

    if (apr_pool_create(&pool, NULL) != APR_SUCCESS) {
        return 1;
    }
    apr_file_open_stderr(&errfile, pool);
    apr_getopt_init(&o, pool, argc, argv);

    while (1) {
        char opt;
        status = apr_getopt(o, "s:c", &opt, &arg);
        if (status == APR_EOF) {
            break;
        }
        else if (status != APR_SUCCESS) {
            usage();
        }
        else {
            switch (opt) {
            case 'c':
                if (doublelookups) {
                    usage();
                }
                doublelookups = 1;
                break;
            case 's':
                if (stats) {
                    usage();
                }
                stats = apr_pstrdup(pool, arg);
                break;
            } /* switch */
        } /* else */
    } /* while */

    apr_file_open_stdout(&outfile, pool);
    apr_file_open_stdin(&infile, pool);

    /* Allocate two new 10k file buffers */
    if (   (outbuffer = apr_palloc(pool, WRITE_BUF_SIZE)) == NULL
        || (inbuffer  = apr_palloc(pool, READ_BUF_SIZE))  == NULL
        || (line      = apr_palloc(pool, LINE_BUF_SIZE))  == NULL) {
        return 1;
    }

    /* Set the buffers */
    apr_file_buffer_set(infile, inbuffer, READ_BUF_SIZE);
    apr_file_buffer_set(outfile, outbuffer, WRITE_BUF_SIZE);

    cache = apr_hash_make(pool);
    if (apr_pool_create(&pline, pool) != APR_SUCCESS) {
        return 1;
    }

    while (apr_file_gets(line, LINE_BUF_SIZE, infile) == APR_SUCCESS) {
        char *hostname;
        char *space;
        apr_sockaddr_t *ip;
        apr_sockaddr_t *ipdouble;
        char dummy[] = " " APR_EOL_STR;

        if (line[0] == '\0') {
            continue;
        }

        /* Count our log entries */
        entries++;

        /* Check if this could even be an IP address */
        if (!apr_isxdigit(line[0]) && line[0] != ':') {
            withname++;
            apr_file_puts(line, outfile);
            continue;
        }

        /* Terminate the line at the next space */
        if ((space = strchr(line, ' ')) != NULL) {
            *space = '\0';
        }
        else {
            space = dummy;
        }

        /* See if we have it in our cache */
        hostname = (char *) apr_hash_get(cache, line, APR_HASH_KEY_STRING);
        if (hostname) {
            apr_file_printf(outfile, "%s %s", hostname, space + 1);
            cachehits++;
            continue;
        }

        /* Parse the IP address */
        status = apr_sockaddr_info_get(&ip, line, APR_UNSPEC, 0, 0, pline);
        if (status != APR_SUCCESS) {
            /* Not an IP address */
            withname++;
            *space = ' ';
            apr_file_puts(line, outfile);
            continue;
        }

        /* This does not make much sense, but historically "resolves" means
         * "parsed as an IP address". It does not mean we actually resolved
         * the IP address into a hostname.
         */
        resolves++;

        /* From here on our we cache each result, even if it was not
         * succesful
         */
        cachesize++;

        /* Try and perform a reverse lookup */
        status = apr_getnameinfo(&hostname, ip, 0) != APR_SUCCESS;
        if (status || hostname == NULL) {
            /* Could not perform a reverse lookup */
            *space = ' ';
            apr_file_puts(line, outfile);
            noreverse++;

            /* Add to cache */
            *space = '\0';
            apr_hash_set(cache, line, APR_HASH_KEY_STRING,
                         apr_pstrdup(apr_h
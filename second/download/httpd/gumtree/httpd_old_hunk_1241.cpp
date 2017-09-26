        fprintf(stderr, "apr_base64init_ebcdic()->%d\n", status);
        exit(1);
    }
#endif

    apr_getopt_init(&opt, cntxt, argc, argv);
    while ((status = apr_getopt(opt, "n:c:t:b:T:p:v:rkVhwix:y:z:C:H:P:A:g:X:de:Sq"
#ifdef USE_SSL
            "Z:f:"
#endif
            ,&c, &optarg)) == APR_SUCCESS) {
        switch (c) {
            case 'n':

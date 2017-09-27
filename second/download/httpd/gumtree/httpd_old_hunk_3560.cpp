
    if (argc <= 1) {
        usage();
        return 1;
    }

    while ((rv = apr_getopt(opt, "vf::i::o::", &ch, &optarg)) == APR_SUCCESS) {
        switch (ch) {
        case 'v':
            if (verbose) {
                apr_file_printf(errfile, "Error: -v can only be passed once" NL NL);
                usage();
                return 1;

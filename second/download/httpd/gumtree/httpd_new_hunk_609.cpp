    fprintf(stderr, "    -V              Print version number and exit\n");
    fprintf(stderr, "    -k              Use HTTP KeepAlive feature\n");
    fprintf(stderr, "    -d              Do not show percentiles served table.\n");
    fprintf(stderr, "    -S              Do not show confidence estimators and warnings.\n");
    fprintf(stderr, "    -g filename     Output collected data to gnuplot format file.\n");
    fprintf(stderr, "    -e filename     Output CSV file with percentages served\n");
#ifdef USE_SSL
    fprintf(stderr, "    -s              Use httpS instead of HTTP (SSL)\n");
#endif
    fprintf(stderr, "    -h              Display usage information (this message)\n");
    exit(EINVAL);
}


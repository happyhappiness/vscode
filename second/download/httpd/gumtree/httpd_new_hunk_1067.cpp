    fprintf(stderr, "    -V              Print version number and exit\n");
    fprintf(stderr, "    -k              Use HTTP KeepAlive feature\n");
    fprintf(stderr, "    -d              Do not show percentiles served table.\n");
    fprintf(stderr, "    -S              Do not show confidence estimators and warnings.\n");
    fprintf(stderr, "    -g filename     Output collected data to gnuplot format file.\n");
    fprintf(stderr, "    -e filename     Output CSV file with percentages served\n");
    fprintf(stderr, "    -h              Display usage information (this message)\n");
#ifdef USE_SSL
    fprintf(stderr, "    -Z ciphersuite  Specify SSL/TLS cipher suite (See openssl ciphers)\n");
    fprintf(stderr, "    -f protocol     Specify SSL/TLS protocol (SSL2, SSL3, TLS1, or ALL)\n");
#endif
    exit(EINVAL);
}

/* ------------------------------------------------------- */

/* split URL into parts */

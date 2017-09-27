    fprintf(stderr, "    -g filename     Output collected data to gnuplot format file.\n");
    fprintf(stderr, "    -e filename     Output CSV file with percentages served\n");
    fprintf(stderr, "    -r              Don't exit on socket receive errors.\n");
    fprintf(stderr, "    -h              Display usage information (this message)\n");
#ifdef USE_SSL
    fprintf(stderr, "    -Z ciphersuite  Specify SSL/TLS cipher suite (See openssl ciphers)\n");
    fprintf(stderr, "    -f protocol     Specify SSL/TLS protocol (SSL2, SSL3, TLS1, or ALL)\n");
#endif
    exit(EINVAL);
}

/* ------------------------------------------------------- */


    fprintf(stderr, "    -S              Do not show confidence estimators and warnings.\n");
    fprintf(stderr, "    -q              Do not show progress when doing more than 150 requests\n");
    fprintf(stderr, "    -l              Accept variable document length (use this for dynamic pages)\n");
    fprintf(stderr, "    -g filename     Output collected data to gnuplot format file.\n");
    fprintf(stderr, "    -e filename     Output CSV file with percentages served\n");
    fprintf(stderr, "    -r              Don't exit on socket receive errors.\n");
    fprintf(stderr, "    -h              Display usage information (this message)\n");
#ifdef USE_SSL

#ifndef OPENSSL_NO_SSL2
#define SSL2_HELP_MSG "SSL2, "
#else

    return 0;
}

static void usage(void)
{
    apr_file_printf(errfile, "Usage:" NL
        "\thtpasswd [-cimBdpsDv] [-C cost] passwordfile username" NL
        "\thtpasswd -b[cmBdpsDv] [-C cost] passwordfile username password" NL
        NL
        "\thtpasswd -n[imBdps] [-C cost] username" NL
        "\thtpasswd -nb[mBdps] [-C cost] username password" NL
        " -c  Create a new file." NL
        " -n  Don't update file; display results on stdout." NL
        " -b  Use the password from the command line rather than prompting "

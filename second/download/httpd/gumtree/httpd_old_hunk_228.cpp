    return 0;
}

static void usage(void)
{
    apr_file_printf(errfile, "Usage:\n");
    apr_file_printf(errfile, "\thtpasswd [-cmdps] passwordfile username\n");
    apr_file_printf(errfile, "\thtpasswd -b[cmdps] passwordfile username "
                    "password\n\n");
    apr_file_printf(errfile, "\thtpasswd -n[mdps] username\n");
    apr_file_printf(errfile, "\thtpasswd -nb[mdps] username password\n");
    apr_file_printf(errfile, " -c  Create a new file.\n");
    apr_file_printf(errfile, " -n  Don't update file; display results on "
                    "stdout.\n");

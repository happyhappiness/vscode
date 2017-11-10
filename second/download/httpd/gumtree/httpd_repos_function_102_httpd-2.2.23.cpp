static void usage(void)
{
    apr_file_printf(errfile, "Usage: htdigest [-c] passwordfile realm username\n");
    apr_file_printf(errfile, "The -c flag creates a new file.\n");
    exit(1);
}
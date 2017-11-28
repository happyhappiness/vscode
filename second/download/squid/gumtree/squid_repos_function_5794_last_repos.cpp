void usage(void)
{
    fprintf(stderr, "Usage: \n");
    fprintf(stderr, "negotiate_wrapper [-h] [-d] --ntlm ntlm helper + arguments --kerberos kerberos helper + arguments\n");
    fprintf(stderr, "-h help\n");
    fprintf(stderr, "-d full debug\n");
    fprintf(stderr, "--ntlm full ntlm helper path with arguments\n");
    fprintf(stderr, "--kerberos full kerberos helper path with arguments\n");
}
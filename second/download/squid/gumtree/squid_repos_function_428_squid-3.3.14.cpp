static void usage(char *program)
{
    fprintf(stderr, "Usage: %s [options..]\n", program);
    fprintf(stderr, " -n service_name\n");
    fprintf(stderr, "           The PAM service name (default \"%s\")\n", DEFAULT_SQUID_PAM_SERVICE);
    fprintf(stderr, " -t ttl    PAM connection ttl in seconds (default %d)\n", DEFAULT_SQUID_PAM_TTL);
    fprintf(stderr, "           during this time the same connection will be reused\n");
    fprintf(stderr, "           to authenticate all users\n");
    fprintf(stderr, " -o        Do not perform account mgmt (account expiration etc)\n");
    fprintf(stderr, " -1        Only one user authentication per PAM connection\n");
}
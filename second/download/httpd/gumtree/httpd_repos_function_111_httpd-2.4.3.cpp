static void exit_error(apr_status_t rv, const char *func)
{
    char buffer[1024];

    fprintf(stderr,
            "%s: %s\n",
            func,
            apr_strerror(rv, buffer, sizeof(buffer)));

    exit(EXIT_FAILURE);
}
static void truncate_and_write_error(rotate_status_t *status)
{
    apr_size_t buflen = strlen(status->errbuf);

    if (apr_file_trunc(status->current.fd, 0) != APR_SUCCESS) {
        fprintf(stderr, "Error truncating the file %s\n", status->current.name);
        exit(2);
    }
    if (apr_file_write_full(status->current.fd, status->errbuf, buflen, NULL) != APR_SUCCESS) {
        fprintf(stderr, "Error writing error (%s) to the file %s\n", 
                status->errbuf, status->current.name);
        exit(2);
    }
}
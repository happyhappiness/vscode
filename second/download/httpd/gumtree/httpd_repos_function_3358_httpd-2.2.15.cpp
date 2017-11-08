int main(int argc, char *argv[])
{
    apr_file_t *in, *out;
    apr_size_t nbytes, total_bytes;
    apr_pool_t *p;
    char buf[128];
    apr_status_t rv;
    
    apr_initialize();
    atexit(apr_terminate);
    apr_pool_create(&p, NULL);

    apr_file_open_stdin(&in, p);
    apr_file_open_stdout(&out, p);

    total_bytes = 0;
    nbytes = sizeof(buf);
    while ((rv = apr_file_read(in, buf, &nbytes)) == APR_SUCCESS) {
        total_bytes += nbytes;
        nbytes = sizeof(buf);
    }

    apr_file_printf(out, "%" APR_SIZE_T_FMT " bytes were read\n",
                    total_bytes);
    return 0;
}
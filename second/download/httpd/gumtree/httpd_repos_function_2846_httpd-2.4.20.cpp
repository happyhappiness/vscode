static apr_status_t arout(sed_eval_t *eval)
{
    apr_status_t rv = APR_SUCCESS;
    eval->aptr = eval->abuf - 1;
    while (*++eval->aptr) {
        if ((*eval->aptr)->command == ACOM) {
            char *p1;

            for (p1 = (*eval->aptr)->re1; *p1; p1++);
            rv = wline(eval, (*eval->aptr)->re1, p1 - (*eval->aptr)->re1);
            if (rv != APR_SUCCESS)
                return rv;
        } else {
            apr_file_t *fi = NULL;
            char buf[512];
            apr_size_t n = sizeof(buf);

            if (apr_file_open(&fi, (*eval->aptr)->re1, APR_READ, 0, eval->pool)
                              != APR_SUCCESS)
                continue;
            while ((apr_file_read(fi, buf, &n)) == APR_SUCCESS) {
                if (n == 0)
                    break;
                rv = eval->writefn(eval->fout, buf, n);
                if (rv != APR_SUCCESS) {
                    apr_file_close(fi);
                    return rv;
                }
                n = sizeof(buf);
            }
            apr_file_close(fi);
        }
    }
    eval->aptr = eval->abuf;
    *eval->aptr = NULL;
    return rv;
}
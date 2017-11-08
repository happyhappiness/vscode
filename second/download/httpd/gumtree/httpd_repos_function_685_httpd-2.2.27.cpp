static char *ssl_expr_eval_func_file(request_rec *r, char *filename)
{
    apr_file_t *fp;
    char *buf;
    apr_off_t offset;
    apr_size_t len;
    apr_finfo_t finfo;

    if (apr_file_open(&fp, filename, APR_READ|APR_BUFFERED,
                      APR_OS_DEFAULT, r->pool) != APR_SUCCESS) {
        ssl_expr_error = "Cannot open file";
        return "";
    }
    apr_file_info_get(&finfo, APR_FINFO_SIZE, fp);
    if ((finfo.size + 1) != ((apr_size_t)finfo.size + 1)) {
        ssl_expr_error = "Huge file cannot be read";
        apr_file_close(fp);
        return "";
    }
    len = (apr_size_t)finfo.size;
    if (len == 0) {
        buf = (char *)apr_palloc(r->pool, sizeof(char) * 1);
        *buf = NUL;
    }
    else {
        if ((buf = (char *)apr_palloc(r->pool, sizeof(char)*(len+1))) == NULL) {
            ssl_expr_error = "Cannot allocate memory";
            apr_file_close(fp);
            return "";
        }
        offset = 0;
        apr_file_seek(fp, APR_SET, &offset);
        if (apr_file_read(fp, buf, &len) != APR_SUCCESS) {
            ssl_expr_error = "Cannot read from file";
            apr_file_close(fp);
            return "";
        }
        buf[len] = NUL;
    }
    apr_file_close(fp);
    return buf;
}
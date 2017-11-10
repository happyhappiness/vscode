static const char *file_func(ap_expr_eval_ctx_t *ctx, const void *data,
                             char *arg)
{
    apr_file_t *fp;
    char *buf;
    apr_off_t offset;
    apr_size_t len;
    apr_finfo_t finfo;

    if (apr_file_open(&fp, arg, APR_READ|APR_BUFFERED,
                      APR_OS_DEFAULT, ctx->p) != APR_SUCCESS) {
        *ctx->err = apr_psprintf(ctx->p, "Cannot open file %s", arg);
        return "";
    }
    apr_file_info_get(&finfo, APR_FINFO_SIZE, fp);
    if (finfo.size > MAX_FILE_SIZE) {
        *ctx->err = apr_psprintf(ctx->p, "File %s too large", arg);
        apr_file_close(fp);
        return "";
    }
    len = (apr_size_t)finfo.size;
    if (len == 0) {
        apr_file_close(fp);
        return "";
    }
    else {
        if ((buf = (char *)apr_palloc(ctx->p, sizeof(char)*(len+1))) == NULL) {
            *ctx->err = "Cannot allocate memory";
            apr_file_close(fp);
            return "";
        }
        offset = 0;
        apr_file_seek(fp, APR_SET, &offset);
        if (apr_file_read(fp, buf, &len) != APR_SUCCESS) {
            *ctx->err = apr_psprintf(ctx->p, "Cannot read from file %s", arg);
            apr_file_close(fp);
            return "";
        }
        buf[len] = '\0';
    }
    apr_file_close(fp);
    return buf;
}
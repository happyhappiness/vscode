   return 0;
}

void putline(apr_file_t *f, const char *l)
{
    apr_status_t rv;
    rv = apr_file_puts(l, f);
    if (rv != APR_SUCCESS) {
        apr_file_printf(errfile, "Error writing temp file: %pm", &rv);
        apr_file_close(f);
        exit(ERR_FILEPERM);
    }
}

int get_password(struct passwd_ctx *ctx)
{
    if (ctx->passwd_src == PW_STDIN) {
        char *buf = ctx->out;
        apr_file_t *file_stdin;
        apr_size_t nread;
        if (apr_file_open_stdin(&file_stdin, ctx->pool) != APR_SUCCESS) {
            ctx->errstr = "Unable to read from stdin.";
            return ERR_GENERAL;
        }
        if (apr_file_read_full(file_stdin, buf, ctx->out_len - 1,
                               &nread) != APR_EOF
            || nread == ctx->out_len - 1) {
            goto err_too_long;
        }
        buf[nread] = '\0';
        if (nread >= 1 && buf[nread-1] == '\n') {
            buf[nread-1] = '\0';
            if (nread >= 2 && buf[nread-2] == '\r')
                buf[nread-2] = '\0';
        }
        apr_file_close(file_stdin);
    }
    else {
        char buf[MAX_STRING_LEN + 1];
        apr_size_t bufsize = sizeof(buf);
        if (apr_password_get("New password: ", ctx->out, &ctx->out_len) != 0)
            goto err_too_long;
        apr_password_get("Re-type new password: ", buf, &bufsize);
        if (strcmp(ctx->out, buf) != 0) {
            ctx->errstr = "password verification error";
            memset(ctx->out, '\0', ctx->out_len);
            memset(buf, '\0', sizeof(buf));
            return ERR_PWMISMATCH;
        }
        memset(buf, '\0', sizeof(buf));
    }
    return 0;

err_too_long:
    ctx->errstr = apr_psprintf(ctx->pool,
                               "password too long (>%" APR_SIZE_T_FMT ")",
                               ctx->out_len - 1);

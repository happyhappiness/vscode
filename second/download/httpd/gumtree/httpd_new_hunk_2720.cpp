        tmp_bb = ctx->linebb;
        ctx->linebb = ctx->linesbb;
        ctx->linesbb = tmp_bb;
    }

    return APR_SUCCESS;
err:
    if (rv == APR_ENOMEM)
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, f->r, APLOGNO(01328) "Line too long, URI %s",
                      f->r->uri);
    apr_pool_clear(ctx->tpool);
    return rv;
}

static const char *set_pattern(cmd_parms *cmd, void *cfg, const char *line)
{
    char *from = NULL;
    char *to = NULL;

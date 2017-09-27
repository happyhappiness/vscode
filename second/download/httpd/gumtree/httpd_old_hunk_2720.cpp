        tmp_bb = ctx->linebb;
        ctx->linebb = ctx->linesbb;
        ctx->linesbb = tmp_bb;
    }

    return APR_SUCCESS;
}

static const char *set_pattern(cmd_parms *cmd, void *cfg, const char *line)
{
    char *from = NULL;
    char *to = NULL;

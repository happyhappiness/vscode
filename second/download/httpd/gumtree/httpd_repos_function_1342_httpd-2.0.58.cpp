static void ap_ssi_get_tag_and_value(include_ctx_t *ctx, char **tag,
                                     char **tag_val, int dodecode)
{
    *tag_val = NULL;
    if (ctx->curr_tag_pos >= ctx->combined_tag + ctx->tag_length) {
        *tag = NULL;
        return;
    }

    *tag = ctx->curr_tag_pos;
    if (!**tag) {
        *tag = NULL;
        /* finitio */
        ctx->curr_tag_pos = ctx->combined_tag + ctx->tag_length;
        return;
    }

    *tag_val = ap_strchr(*tag, '=');
    if (!*tag_val) {
        ctx->curr_tag_pos = ctx->combined_tag + ctx->tag_length;
        return;
    }

    /* if it starts with '=' there was no tag name, just a value */
    if (*tag_val == *tag) {
        *tag = NULL;
    }

    *(*tag_val)++ = '\0';
    ctx->curr_tag_pos = *tag_val + strlen(*tag_val) + 1; /* skip \0 byte */

    if (dodecode) {
        decodehtml(*tag_val);
    }

    return;
}
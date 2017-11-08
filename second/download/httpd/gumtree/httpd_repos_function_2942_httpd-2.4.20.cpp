static void ap_ssi_get_tag_and_value(include_ctx_t *ctx, char **tag,
                                     char **tag_val, int dodecode)
{
    if (!ctx->intern->argv) {
        *tag = NULL;
        *tag_val = NULL;

        return;
    }

    *tag_val = ctx->intern->argv->value;
    *tag = ctx->intern->argv->name;

    ctx->intern->argv = ctx->intern->argv->next;

    if (dodecode && *tag_val) {
        decodehtml(*tag_val);
    }
}
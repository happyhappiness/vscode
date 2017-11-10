static int discard_variant_by_env(var_rec *variant, int discard)
{
    if (   is_identity_encoding(variant->content_encoding)
        || !strcmp(variant->content_encoding, "identity")) {
        return 0;
    }

    return (   (discard == DISCARD_ALL_ENCODINGS)
            || (discard == DISCARD_ALL_BUT_HTML
                && (!variant->mime_type
                    || strncmp(variant->mime_type, "text/html", 9))));
}
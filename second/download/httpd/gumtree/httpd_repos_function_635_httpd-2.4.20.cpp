static void register_format_tag_handler(const char *tag,
                                        format_tag_fn *tag_handler)
{
    apr_hash_set(format_tag_hash, tag, 1, tag_handler);
}
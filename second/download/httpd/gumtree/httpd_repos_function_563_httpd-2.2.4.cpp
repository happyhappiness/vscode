static void register_format_tag_handler(const char *tag,
                                        const void *tag_handler)
{
    apr_hash_set(format_tag_hash, tag, 1, tag_handler);
}
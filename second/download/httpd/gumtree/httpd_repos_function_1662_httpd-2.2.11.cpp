static void ap_register_include_handler(char *tag, include_handler_fn_t *func)
{
    apr_hash_set(include_handlers, tag, strlen(tag), (const void *)func);
}
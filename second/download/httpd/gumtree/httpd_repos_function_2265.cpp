static void ap_session_get(request_rec * r, session_rec * z, const char *key, const char **value)
{
    if (!z) {
        ap_session_load(r, &z);
    }
    if (z && z->entries) {
        *value = apr_table_get(z->entries, key);
    }
}
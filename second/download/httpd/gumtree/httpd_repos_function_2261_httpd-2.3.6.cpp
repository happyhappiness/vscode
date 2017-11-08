static void ap_session_set(request_rec * r, session_rec * z,
                                const char *key, const char *value)
{
    if (!z) {
        ap_session_load(r, &z);
    }
    if (z) {
        if (value) {
            apr_table_set(z->entries, key, value);
        }
        else {
            apr_table_unset(z->entries, key);
        }
        z->dirty = 1;
    }
}
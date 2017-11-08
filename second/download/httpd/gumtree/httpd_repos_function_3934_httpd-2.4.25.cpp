static int protocol_cmp(const apr_array_header_t *preferences,
                        const char *proto1,
                        const char *proto2)
{
    if (preferences && preferences->nelts > 0) {
        int index1 = ap_array_str_index(preferences, proto1, 0);
        int index2 = ap_array_str_index(preferences, proto2, 0);
        if (index2 > index1) {
            return (index1 >= 0) ? 1 : -1;
        }
        else if (index1 > index2) {
            return (index2 >= 0) ? -1 : 1;
        }
    }
    /* both have the same index (mabye -1 or no pref configured) and we compare
     * the names so that spdy3 gets precedence over spdy2. That makes
     * the outcome at least deterministic. */
    return strcmp(proto1, proto2);
}
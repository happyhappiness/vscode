static int h2_push_diary_find(h2_push_diary *diary, apr_uint64_t hash)
{
    if (diary) {
        h2_push_diary_entry *e;
        int i;

        /* search from the end, where the last accessed digests are */
        for (i = diary->entries->nelts-1; i >= 0; --i) {
            e = &APR_ARRAY_IDX(diary->entries, i, h2_push_diary_entry);
            if (e->hash == hash) {
                return i;
            }
        }
    }
    return -1;
}
static void *merge_ct_filters(apr_pool_t *p,
                              const void *key,
                              apr_ssize_t klen,
                              const void *overlay_val,
                              const void *base_val,
                              const void *data)
{
    ap_filter_rec_t *cur;
    const ap_filter_rec_t *overlay_info = (const ap_filter_rec_t *)overlay_val;
    const ap_filter_rec_t *base_info = (const ap_filter_rec_t *)base_val;

    cur = NULL;

    while (overlay_info) {
        ap_filter_rec_t *new;

        new = apr_pcalloc(p, sizeof(ap_filter_rec_t));
        new->name = apr_pstrdup(p, overlay_info->name);
        new->next = cur;
        cur = new;
        overlay_info = overlay_info->next;
    }

    while (base_info) {
        ap_filter_rec_t *f;
        int found = 0;

        /* We can't have dups. */
        f = cur;
        while (f) {
            if (!strcasecmp(base_info->name, f->name)) {
                found = 1;
                break;
            }

            f = f->next;
        }

        if (!found) {
            f = apr_pcalloc(p, sizeof(ap_filter_rec_t));
            f->name = apr_pstrdup(p, base_info->name);
            f->next = cur;
            cur = f;
        }

        base_info = base_info->next;
    }

    return cur;
}
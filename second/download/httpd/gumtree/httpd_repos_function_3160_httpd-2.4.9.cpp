static void remove_any_filter(ap_filter_t *f, ap_filter_t **r_filt, ap_filter_t **p_filt,
                              ap_filter_t **c_filt)
{
    ap_filter_t **curr = r_filt ? r_filt : c_filt;
    ap_filter_t *fscan = *curr;

    if (p_filt && *p_filt == f)
        *p_filt = (*p_filt)->next;

    if (*curr == f) {
        *curr = (*curr)->next;
        return;
    }

    while (fscan->next != f) {
        if (!(fscan = fscan->next)) {
            return;
        }
    }

    fscan->next = f->next;
}
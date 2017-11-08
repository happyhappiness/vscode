static int ignore_entry(autoindex_config_rec *d, char *path)
{
    apr_array_header_t *list = d->ign_list;
    struct item *items = (struct item *) list->elts;
    char *tt;
    int i;

    if ((tt = strrchr(path, '/')) == NULL) {
        tt = path;
    }
    else {
        tt++;
    }

    for (i = 0; i < list->nelts; ++i) {
        struct item *p = &items[i];
        char *ap;

        if ((ap = strrchr(p->apply_to, '/')) == NULL) {
            ap = p->apply_to;
        }
        else {
            ap++;
        }

#ifndef CASE_BLIND_FILESYSTEM
        if (!ap_strcmp_match(path, p->apply_path)
            && !ap_strcmp_match(tt, ap)) {
            return 1;
        }
#else  /* !CASE_BLIND_FILESYSTEM */
        /*
         * On some platforms, the match must be case-blind.  This is really
         * a factor of the filesystem involved, but we can't detect that
         * reliably - so we have to granularise at the OS level.
         */
        if (!ap_strcasecmp_match(path, p->apply_path)
            && !ap_strcasecmp_match(tt, ap)) {
            return 1;
        }
#endif /* !CASE_BLIND_FILESYSTEM */
    }
    return 0;
}
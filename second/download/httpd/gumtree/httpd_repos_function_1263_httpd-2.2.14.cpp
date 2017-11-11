static struct ent *make_parent_entry(apr_int32_t autoindex_opts,
                                     autoindex_config_rec *d,
                                     request_rec *r, char keyid,
                                     char direction)
{
    struct ent *p = (struct ent *) apr_pcalloc(r->pool, sizeof(struct ent));
    char *testpath;
    /*
     * p->name is now the true parent URI.
     * testpath is a crafted lie, so that the syntax '/some/..'
     * (or simply '..')be used to describe 'up' from '/some/'
     * when processeing IndexIgnore, and Icon|Alt|Desc configs.
     */

    /* The output has always been to the parent.  Don't make ourself
     * our own parent (worthless cyclical reference).
     */
    if (!(p->name = ap_make_full_path(r->pool, r->uri, "../"))) {
        return (NULL);
    }
    ap_getparents(p->name);
    if (!*p->name) {
        return (NULL);
    }

    /* IndexIgnore has always compared "/thispath/.." */
    testpath = ap_make_full_path(r->pool, r->filename, "..");
    if (ignore_entry(d, testpath)) {
        return (NULL);
    }

    p->size = -1;
    p->lm = -1;
    p->key = apr_toupper(keyid);
    p->ascending = (apr_toupper(direction) == D_ASCENDING);
    p->version_sort = autoindex_opts & VERSION_SORT;
    if (autoindex_opts & FANCY_INDEXING) {
        if (!(p->icon = find_default_icon(d, testpath))) {
            p->icon = find_default_icon(d, "^^DIRECTORY^^");
        }
        if (!(p->alt = find_default_alt(d, testpath))) {
            if (!(p->alt = find_default_alt(d, "^^DIRECTORY^^"))) {
                p->alt = "DIR";
            }
        }
        p->desc = find_desc(d, testpath);
    }
    return p;
}
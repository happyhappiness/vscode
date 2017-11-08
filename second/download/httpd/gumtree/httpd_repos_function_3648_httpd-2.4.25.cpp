static apr_status_t groups_for_user(apr_pool_t *p, char *user, char *grpfile,
                                    apr_table_t ** out)
{
    ap_configfile_t *f;
    apr_table_t *grps = apr_table_make(p, 15);
    apr_pool_t *sp;
    struct ap_varbuf vb;
    const char *group_name, *ll, *w;
    apr_status_t status;
    apr_size_t group_len;

    if ((status = ap_pcfg_openfile(&f, p, grpfile)) != APR_SUCCESS) {
        return status ;
    }

    apr_pool_create(&sp, p);
    ap_varbuf_init(p, &vb, VARBUF_INIT_LEN);

    while (!(ap_varbuf_cfg_getline(&vb, f, VARBUF_MAX_LEN))) {
        if ((vb.buf[0] == '#') || (!vb.buf[0])) {
            continue;
        }
        ll = vb.buf;
        apr_pool_clear(sp);

        group_name = ap_getword(sp, &ll, ':');
        group_len = strlen(group_name);

        while (group_len && apr_isspace(*(group_name + group_len - 1))) {
            --group_len;
        }

        while (ll[0]) {
            w = ap_getword_conf(sp, &ll);
            if (!strcmp(w, user)) {
                apr_table_setn(grps, apr_pstrmemdup(p, group_name, group_len),
                               "in");
                break;
            }
        }
    }
    ap_cfg_closefile(f);
    apr_pool_destroy(sp);
    ap_varbuf_free(&vb);

    *out = grps;
    return APR_SUCCESS;
}
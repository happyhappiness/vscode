static int includes_setup(ap_filter_t *f)
{
    include_dir_config *conf = ap_get_module_config(f->r->per_dir_config,
                                                    &include_module);

    /* When our xbithack value isn't set to full or our platform isn't
     * providing group-level protection bits or our group-level bits do not
     * have group-execite on, we will set the no_local_copy value to 1 so
     * that we will not send 304s.
     */
    if ((conf->xbithack != XBITHACK_FULL)
        || !(f->r->finfo.valid & APR_FINFO_GPROT)
        || !(f->r->finfo.protection & APR_GEXECUTE)) {
        f->r->no_local_copy = 1;
    }

    /* Don't allow ETag headers to be generated - see RFC2616 - 13.3.4.
     * We don't know if we are going to be including a file or executing
     * a program - in either case a strong ETag header will likely be invalid.
     */
    if (conf->etag <= 0) {
        apr_table_setn(f->r->notes, "no-etag", "");
    }

    return OK;
}
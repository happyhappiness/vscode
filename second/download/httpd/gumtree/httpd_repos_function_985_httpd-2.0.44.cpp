static int hook_mimetype(request_rec *r)
{
    const char *t;

    /* now check if we have to force a MIME-type */
    t = apr_table_get(r->notes, REWRITE_FORCED_MIMETYPE_NOTEVAR);
    if (t == NULL) {
        return DECLINED;
    }
    else {
        rewritelog(r, 1, "force filename %s to have MIME-type '%s'",
                   r->filename, t);
        ap_set_content_type(r, t);
        return OK;
    }
}
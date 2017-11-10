static int hook_mimetype(request_rec *r)
{
    const char *t;

    /* type */
    t = apr_table_get(r->notes, REWRITE_FORCED_MIMETYPE_NOTEVAR);
    if (t && *t) {
        rewritelog((r, 1, NULL, "force filename %s to have MIME-type '%s'",
                    r->filename, t));

        ap_set_content_type(r, t);
    }

    /* handler */
    t = apr_table_get(r->notes, REWRITE_FORCED_HANDLER_NOTEVAR);
    if (t && *t) {
        rewritelog((r, 1, NULL, "force filename %s to have the "
                    "Content-handler '%s'", r->filename, t));

        r->handler = t;
    }

    return OK;
}
void h2_ngn_shed_abort(h2_ngn_shed *shed)
{
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, shed->c, APLOGNO(03394)
                  "h2_ngn_shed(%ld): abort", shed->c->id);
    shed->aborted = 1;
}
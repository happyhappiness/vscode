ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, shed->c,
                      "h2_ngn_shed(%ld): abort while pulling requests %s", 
                      shed->c->id, ngn->id);
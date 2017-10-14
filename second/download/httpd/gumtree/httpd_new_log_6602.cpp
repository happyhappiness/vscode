ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, shed->c,
                      "h2_ngn_shed(%ld): exit engine %s (%s), "
                      "has still requests queued, shutdown=%d,"
                      "assigned=%ld, live=%ld, finished=%ld", 
                      shed->c->id, ngn->id, ngn->type,
                      ngn->shutdown, 
                      (long)ngn->no_assigned, (long)ngn->no_live,
                      (long)ngn->no_finished);
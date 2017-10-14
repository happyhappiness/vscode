ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, shed->c,
                      "h2_ngn_shed(%ld): exit engine %s (%s), "
                      "assigned=%ld, live=%ld, finished=%ld", 
                      shed->c->id, ngn->id, ngn->type,
                      (long)ngn->no_assigned, (long)ngn->no_live,
                      (long)ngn->no_finished);
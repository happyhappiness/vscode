ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01644)
                          "authz_dbd: %s of user %s updated %d rows",
                          action, r->user, nrows);
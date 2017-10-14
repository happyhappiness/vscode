ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                          "authz_dbd: %s of user %s updated %d rows",
                          action, r->user, nrows);
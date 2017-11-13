ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01296)
                          "User %s not found in subgroup (%s) at level %d of "
                          "%d.", r->user, group, cur_subgroup_depth+1,
                          max_subgroup_depth);
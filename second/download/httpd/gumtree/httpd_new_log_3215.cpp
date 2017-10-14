ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01714)
                      "auth_ldap authorize: require group: testing for %s: "
                      "%s (%s)",
                      ent[i].name,
                      sec->group_attrib_is_dn ? req->dn : req->user, t);
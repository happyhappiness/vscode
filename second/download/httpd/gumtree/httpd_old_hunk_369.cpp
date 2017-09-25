                     * chance to set the user field. Do so now. */
                    req->user = r->user;
                }
            }

            ap_log_rerror(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, r, 
                          "[%d] auth_ldap authorise: require group: testing for group membership in `%s'", 
		          getpid(), t);

            for (i = 0; i < sec->groupattr->nelts; i++) {
	        ap_log_rerror(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, r, 
                              "[%d] auth_ldap authorise: require group: testing for %s: %s (%s)", getpid(),
                              ent[i].name, sec->group_attrib_is_dn ? req->dn : req->user, t);

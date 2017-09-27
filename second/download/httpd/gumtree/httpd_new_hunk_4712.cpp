            if (newfname && r->args && *r->args) {
                char *qs = strrchr(newfname, '?');
                if (qs && !strcmp(qs+1, r->args)) {
                    *qs = '\0';
                }
            }
        }

        if (newfname) {
            newfname = ap_strchr(newfname, '/');
            r->filename = newfname;
        }
    }

    ap_add_common_vars(r);
    ap_add_cgi_vars(r);

    /* XXX are there any FastCGI specific env vars we need to send? */

    /* Give admins final option to fine-tune env vars */
    fix_cgivars(r, dconf);

    /* XXX mod_cgi/mod_cgid use ap_create_environment here, which fills in

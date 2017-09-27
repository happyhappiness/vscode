                    return decl_die(access_status, "check user", r);
                }
                if ((access_status = ap_run_auth_checker(r)) != OK) {
                    return decl_die(access_status, "check authorization", r);
                }
            }
            break;
        }
    }
    /* XXX Must make certain the ap_run_type_checker short circuits mime
     * in mod-proxy for r->proxyreq && r->parsed_uri.scheme
     *                              && !strcmp(r->parsed_uri.scheme, "http")

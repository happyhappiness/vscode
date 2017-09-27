            ret = prvdraliasrec->provider->
                check_authorization(r, prvdraliasrec->provider_args,
                                    prvdraliasrec->provider_parsed_args);

            r->per_dir_config = orig_dir_config;
        }
        else {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02305)
                          "no alias provider found for '%s' (BUG?)",
                          provider_name);
        }
    }
    else {
        ap_assert(provider_name != NULL);
    }

    return ret;
}

static const authz_provider authz_alias_provider =

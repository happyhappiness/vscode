            ret = prvdraliasrec->provider->
                check_authorization(r, prvdraliasrec->provider_args,
                                    prvdraliasrec->provider_parsed_args);

            r->per_dir_config = orig_dir_config;
        }
    }

    return ret;
}

static const authz_provider authz_alias_provider =

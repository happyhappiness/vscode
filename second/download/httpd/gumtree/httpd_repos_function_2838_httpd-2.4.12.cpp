static void *merge_auth_basic_dir_config(apr_pool_t *p, void *basev, void *overridesv)
{
    auth_basic_config_rec *newconf = apr_pcalloc(p, sizeof(*newconf));
    auth_basic_config_rec *base = basev;
    auth_basic_config_rec *overrides = overridesv;

    newconf->authoritative =
            overrides->authoritative_set ? overrides->authoritative :
                    base->authoritative;
    newconf->authoritative_set = overrides->authoritative_set
            || base->authoritative_set;

    newconf->fakeuser =
            overrides->fake_set ? overrides->fakeuser : base->fakeuser;
    newconf->fakepass =
            overrides->fake_set ? overrides->fakepass : base->fakepass;
    newconf->fake_set = overrides->fake_set || base->fake_set;

    newconf->use_digest_algorithm =
        overrides->use_digest_algorithm_set ? overrides->use_digest_algorithm
                                            : base->use_digest_algorithm;
    newconf->use_digest_algorithm_set =
        overrides->use_digest_algorithm_set || base->use_digest_algorithm_set;

    newconf->providers = overrides->providers ? overrides->providers : base->providers;

    return newconf;
}
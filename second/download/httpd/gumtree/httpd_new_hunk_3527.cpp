        log_perms_failure(rv, s, type);
    }
#endif

    return rv;
}

AP_CORE_DECLARE(void) ap_dump_mutexes(apr_pool_t *p, server_rec *s, apr_file_t *out)
{
    apr_hash_index_t *idx;
    mutex_cfg_t *defcfg = apr_hash_get(mxcfg_by_type, "default", APR_HASH_KEY_STRING);
    for (idx = apr_hash_first(p, mxcfg_by_type); idx; idx = apr_hash_next(idx))
    {
        mutex_cfg_t *mxcfg;
        const char *name, *mech;
        const void *name_;
        const char *dir = "";
        apr_hash_this(idx, &name_, NULL, NULL);
        name = name_;
        mxcfg = mxcfg_lookup(p, name);
        if (mxcfg == defcfg && strcmp(name, "default") != 0) {
            apr_file_printf(out, "Mutex %s: using_defaults\n", name);
            continue;
        }
        if (mxcfg->none) {
            apr_file_printf(out, "Mutex %s: none\n", name);
            continue;
        }
        switch (mxcfg->mech) {
        case APR_LOCK_DEFAULT:
            mech = "default";
            break;
#if APR_HAS_FCNTL_SERIALIZE
        case APR_LOCK_FCNTL:
            mech = "fcntl";
            break;
#endif
#if APR_HAS_FLOCK_SERIALIZE
        case APR_LOCK_FLOCK:
            mech = "flock";
            break;
#endif
#if APR_HAS_POSIXSEM_SERIALIZE
        case APR_LOCK_POSIXSEM:
            mech = "posixsem";
            break;
#endif
#if APR_HAS_SYSVSEM_SERIALIZE
        case APR_LOCK_SYSVSEM:
            mech = "sysvsem";
            break;
#endif
#if APR_HAS_PROC_PTHREAD_SERIALIZE
        case APR_LOCK_PROC_PTHREAD:
            mech = "pthread";
            break;
#endif
        default:
            ap_assert(0);
        }

        if (mxcfg->dir)
            dir = ap_server_root_relative(p, mxcfg->dir);

        apr_file_printf(out, "Mutex %s: dir=\"%s\" mechanism=%s %s\n", name, dir, mech,
                        mxcfg->omit_pid ? "[OmitPid]" : "");
    }
}

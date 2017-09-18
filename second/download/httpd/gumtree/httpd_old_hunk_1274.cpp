
        result = apr_global_mutex_create(&st->util_ldap_cache_lock, st->lock_file, APR_LOCK_DEFAULT, st->pool);
        if (result != APR_SUCCESS) {
            return result;
        }

        /* merge config in all vhost */
        s_vhost = s->next;
        while (s_vhost) {
            st_vhost = (util_ldap_state_t *)ap_get_module_config(s_vhost->module_config, &ldap_module);

#if APR_HAS_SHARED_MEMORY

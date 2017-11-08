static apr_ldap_rebind_entry_t *apr_ldap_rebind_lookup(LDAP *ld)
{
    apr_ldap_rebind_entry_t *tmp_xref, *match = NULL;

#ifdef NETWARE
    get_apd
#endif

#if APR_HAS_THREADS
    apr_thread_mutex_lock(apr_ldap_xref_lock);
#endif
    tmp_xref = xref_head;

    while (tmp_xref) {
        if (tmp_xref->index == ld) {
            match = tmp_xref;
            tmp_xref = NULL;
        }
        else {
            tmp_xref = tmp_xref->next;
        }
    }

#if APR_HAS_THREADS
    apr_thread_mutex_unlock(apr_ldap_xref_lock);
#endif

    return (match);
}
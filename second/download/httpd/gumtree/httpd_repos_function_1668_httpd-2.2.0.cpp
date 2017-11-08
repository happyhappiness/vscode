static int nwssl_pre_config(apr_pool_t *pconf, apr_pool_t *plog,
                         apr_pool_t *ptemp)
{
    seclisten_rec* ap_old_seclisteners;
    char *ports, *addr;
    unsigned short port;
    ap_listen_rec **walk;
    seclisten_rec **secwalk;
    apr_sockaddr_t *sa;
    int found;

  /* Pull all of the listeners that were created by mod_nw_ssl out of the
     ap_listeners list so that the normal listen socket processing does
     automatically close them */
    nw_old_listeners = NULL;
    ap_old_seclisteners = NULL;

    for (secwalk = &ap_seclisteners; *secwalk;) {
        found = 0;
        for (walk = &ap_listeners; *walk;) {
            sa = (*walk)->bind_addr;
            if (sa) {
                ap_listen_rec *new;
                seclisten_rec *secnew;
                apr_port_t oldport;

                oldport = sa->port;
                /* If both ports are equivalent, then if their names are equivalent,
                 * then we will re-use the existing record.
                 */
                if ((*secwalk)->port == oldport &&
                    ((!(*secwalk)->addr && !sa->hostname) ||
                     (((*secwalk)->addr && sa->hostname) && !strcmp(sa->hostname, (*secwalk)->addr)))) {
                    /* Move the listen socket from ap_listeners to nw_old_listeners */
                    new = *walk;
                    *walk = new->next;
                    new->next = nw_old_listeners;
                    nw_old_listeners = new;

                    /* Move the secure socket record to ap_old_seclisterners */
                    secnew = *secwalk;
                    *secwalk = secnew->next;
                    secnew->next = ap_old_seclisteners;
                    ap_old_seclisteners = secnew;
                    found = 1;
                    break;
                }
            }

            walk = &(*walk)->next;
        }
        if (!found && &(*secwalk)->next) {
            secwalk = &(*secwalk)->next;
        }
    }

    /* Restore the secure socket records list so that the post config can
       process all of the sockets normally */
    ap_seclisteners = ap_old_seclisteners;
    ap_seclistenersup = NULL;
    certlist = apr_array_make(pconf, 1, sizeof(char *));

    /* Now that we have removed all of the mod_nw_ssl created socket records,
       allow the normal listen socket handling to occur.
       NOTE: If for any reason mod_nw_ssl is removed as a built-in module,
       the following call must be put back into the pre-config handler of the
       MPM.  It is only here to ensure that mod_nw_ssl fixes up the listen
       socket list before anything else looks at it. */
    ap_listen_pre_config();

    return OK;
}
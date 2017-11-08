static apr_status_t call_resolver(apr_sockaddr_t **sa,
                                  const char *hostname, apr_int32_t family,
                                  apr_port_t port, apr_int32_t flags, 
                                  apr_pool_t *p)
{
    struct addrinfo hints, *ai, *ai_list;
    apr_sockaddr_t *prev_sa;
    int error;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = family;
    hints.ai_socktype = SOCK_STREAM;
    error = getaddrinfo(hostname, NULL, &hints, &ai_list);
    if (error) {
#ifndef WIN32
        if (error == EAI_SYSTEM) {
            return errno;
        }
        else 
#endif
        {
            /* issues with representing this with APR's error scheme:
             * glibc uses negative values for these numbers, perhaps so 
             * they don't conflict with h_errno values...  Tru64 uses 
             * positive values which conflict with h_errno values
             */
#if defined(NEGATIVE_EAI)
            error = -error;
#endif
            return error + APR_OS_START_EAIERR;
        }
    }

    prev_sa = NULL;
    ai = ai_list;
    while (ai) { /* while more addresses to report */
        apr_sockaddr_t *new_sa = apr_pcalloc(p, sizeof(apr_sockaddr_t));

        new_sa->pool = p;
        memcpy(&new_sa->sa, ai->ai_addr, ai->ai_addrlen);
        apr_sockaddr_vars_set(new_sa, ai->ai_family, port);

        if (!prev_sa) { /* first element in new list */
            new_sa->hostname = apr_pstrdup(p, hostname);
            *sa = new_sa;
        }
        else {
            prev_sa->next = new_sa;
        }

        prev_sa = new_sa;
        ai = ai->ai_next;
    }
    freeaddrinfo(ai_list);
    return APR_SUCCESS;
}
static void
lookup(const char *buf)
{
    int ttl = 0;
    int retry = 0;
    unsigned int i = 0;
    char ntoabuf[256];
    struct addrinfo hints;
    struct addrinfo *AI = NULL;
    struct addrinfo *aiptr = NULL;
    struct addrinfo *prev_addr = NULL;
    int res = 0;

    if (0 == strcmp(buf, "$shutdown"))
        exit(0);

    if (0 == strcmp(buf, "$hello")) {
        printf("$alive\n");
        return;
    }

    /* check if it's already an IP address in text form. */
    memset(&hints, '\0', sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_flags = AI_NUMERICHOST; // only succeed if its numeric.
    const bool isDomain = (getaddrinfo(buf,NULL,&hints,&AI) != 0);

    // reset for real lookup
    if (AI != NULL) {
        freeaddrinfo(AI);
        AI = NULL;
    }

    // resolve the address/name
    memset(&hints, '\0', sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_flags = AI_CANONNAME;
    for (;;) {
        if (AI != NULL) {
            freeaddrinfo(AI);
            AI = NULL;
        }

        if ( 0 == (res = getaddrinfo(buf,NULL,&hints,&AI)) )
            break;

        if (res != EAI_AGAIN)
            break;

        if (++retry == 3)
            break;

        sleep(1);
    }

    if (isDomain) {
        /* its a domain name. Use the forward-DNS lookup already done */

        if (res == 0) {
#if LIBRESOLV_DNS_TTL_HACK
            /* DNS TTL handling - bne@CareNet.hu
             * for first try it's a dirty hack, by hacking getanswer
             * to place the ttl in a global variable */
            if (_dns_ttl_ > -1)
                ttl = _dns_ttl_;
#endif
            printf("$addr %d", ttl);

            i = 0;
            aiptr = AI;
            while (NULL != aiptr && 32 >= i) {
                memset(ntoabuf, 0, sizeof(ntoabuf));

                /* getaddrinfo given a host has a nasty tendency to return duplicate addr's */
                /* BUT sorted fortunately, so we can drop most of them easily */
                if ( prev_addr &&
                        prev_addr->ai_family==aiptr->ai_family &&
                        memcmp(aiptr->ai_addr, prev_addr->ai_addr, aiptr->ai_addrlen)==0
                   ) {
                    prev_addr = aiptr;
                    aiptr = aiptr->ai_next;
                    continue;
                } else {
                    prev_addr = aiptr;
                }

                /* annoying inet_ntop breaks the nice code by requiring the in*_addr */
                switch (aiptr->ai_family) {
                case AF_INET:
                    inet_ntop(aiptr->ai_family, &((struct sockaddr_in*)aiptr->ai_addr)->sin_addr, ntoabuf, sizeof(ntoabuf));
                    break;
                case AF_INET6:
                    inet_ntop(aiptr->ai_family, &((struct sockaddr_in6*)aiptr->ai_addr)->sin6_addr, ntoabuf, sizeof(ntoabuf));
                    break;
                default:
                    aiptr = aiptr->ai_next;
                    continue;
                }
                printf(" %s", ntoabuf);
                ++i;
                aiptr = aiptr->ai_next;
            }

            prev_addr=NULL;
            printf("\n");
        }
    } else { /* its an IPA in text form. perform rDNS */
        /* You'd expect getaddrinfo given AI_CANONNAME would do a lookup on
         * missing FQDN. But no, it only copies the input string to that
         * position regardless of its content.
         */
        if (NULL != AI && NULL != AI->ai_addr) {
            for (;;) {
                if ( 0 == (res = getnameinfo(AI->ai_addr, AI->ai_addrlen, ntoabuf, sizeof(ntoabuf), NULL,0,0)) )
                    break;

                if (res != EAI_AGAIN)
                    break;

                if (++retry == 3)
                    break;

                sleep(1);
            }
        }

        if (res == 0) {
#if LIBRESOLV_DNS_TTL_HACK
            /* DNS TTL handling - bne@CareNet.hu
             * for first try it's a dirty hack, by hacking getanswer
             * to place the ttl in a global variable */
            if (_dns_ttl_ > -1)
                ttl = _dns_ttl_;
#endif

            printf("$name %d %s\n", ttl, ntoabuf);
        }
    }

    switch (res) {
    case 0:
        /* no error. */
        break;

    case EAI_AGAIN:
        printf("$fail Name Server for domain '%s' is unavailable.\n", buf);
        break;

    case EAI_FAIL:
        printf("$fail DNS Domain/IP '%s' does not exist: %s.\n", buf, gai_strerror(res));
        break;

#if defined(EAI_NODATA) || defined(EAI_NONAME)
#if EAI_NODATA
        /* deprecated. obsolete on some OS */
    case EAI_NODATA:
#endif
#if EAI_NONAME
    case EAI_NONAME:
#endif
        printf("$fail DNS Domain/IP '%s' exists without any FQDN/IPs: %s.\n", buf, gai_strerror(res));
        break;
#endif
    default:
        printf("$fail A system error occured looking up Domain/IP '%s': %s.\n", buf, gai_strerror(res));
    }

    if (AI != NULL)
        freeaddrinfo(AI);
}
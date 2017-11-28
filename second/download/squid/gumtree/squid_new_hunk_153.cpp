
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

/**
 \ingroup dnsserver
 */
static void

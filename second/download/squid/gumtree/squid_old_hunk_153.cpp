
    case EAI_AGAIN:
        printf("$fail Name Server for domain '%s' is unavailable.\n", buf);
        break;

    case EAI_FAIL:
        printf("$fail DNS Domain/IP '%s' does not exist: %s.\n", buf, xgai_strerror(res));
        break;

#if defined(EAI_NODATA) || defined(EAI_NONAME)
#ifdef EAI_NODATA
        /* deprecated. obsolete on some OS */
    case EAI_NODATA:
#endif
#ifdef EAI_NONAME
    case EAI_NONAME:
#endif
        printf("$fail DNS Domain/IP '%s' exists without any FQDN/IPs: %s.\n", buf, xgai_strerror(res));
        break;
#endif
    default:
        printf("$fail A system error occured looking up Domain/IP '%s': %s.\n", buf, xgai_strerror(res));
    }

    if (AI != NULL)
        xfreeaddrinfo(AI);
}

/**
 \ingroup dnsserver
 */
static void

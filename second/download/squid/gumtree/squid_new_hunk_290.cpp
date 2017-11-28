    fclose (fp);
}

int
getMyPort(void)
{
    AnyP::PortCfg *p = NULL;
    if ((p = Config.Sockaddr.http)) {
        // skip any special interception ports
        while (p && (p->intercepted || p->spoof_client_ip))
            p = p->next;
        if (p)
            return p->s.GetPort();
    }

#if USE_SSL
    if ((p = Config.Sockaddr.https)) {
        // skip any special interception ports
        while (p && (p->intercepted || p->spoof_client_ip))
            p = p->next;
        if (p)
            return p->s.GetPort();
    }
#endif

    debugs(21, DBG_CRITICAL, "ERROR: No forward-proxy ports configured.");
    return 0; // Invalid port. This will result in invalid URLs on bad configurations.
}

/*
 * Set the umask to at least the given mask. This is in addition
 * to the umask set at startup
 */

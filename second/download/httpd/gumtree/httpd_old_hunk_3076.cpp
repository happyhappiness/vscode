        }

        /* every zero-byte counts as 8 zero-bits */
        bits = 8 * quads;

        if (bits != 32) {     /* no warning for fully qualified IP address */
            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                         "Warning: NetMask not supplied with IP-Addr; guessing: %s/%ld",
                         inet_ntoa(This->addr), bits);
        }
    }

    This->mask.s_addr = htonl(APR_INADDR_NONE << (32 - bits));

    if (*addr == '\0' && (This->addr.s_addr & ~This->mask.s_addr) != 0) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                     "Warning: NetMask and IP-Addr disagree in %s/%ld",
                     inet_ntoa(This->addr), bits);
        This->addr.s_addr &= This->mask.s_addr;
        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                     "         Set to %s/%ld", inet_ntoa(This->addr), bits);
    }

    if (*addr == '\0') {
        This->matcher = proxy_match_ipaddr;
        return 1;

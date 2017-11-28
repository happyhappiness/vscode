void
Ip::Qos::Config::parseConfigLine()
{
    /* parse options ... */
    char *token;
    /* These are set as appropriate and then used to check whether the initial loop has been done */
    bool mark = false;
    bool tos = false;
    /* Assume preserve is true. We don't set at initialisation as this affects isHitTosActive().
       We have to do this now, as we may never match the 'tos' parameter below */
#if !USE_QOS_TOS
    debugs(3, DBG_CRITICAL, "ERROR: Invalid option 'qos_flows'. QOS features not enabled in this build");
    self_destruct();
#endif

    while ( (token = strtok(NULL, w_space)) ) {

        // Work out TOS or mark. Default to TOS for backwards compatibility
        if (!(mark || tos)) {
            if (strncmp(token, "mark",4) == 0) {
#if SO_MARK && USE_LIBCAP
                mark = true;
                // Assume preserve is true. We don't set at initialisation as this affects isHitNfmarkActive()
#if USE_LIBNETFILTERCONNTRACK
                preserveMissMark = true;
# else // USE_LIBNETFILTERCONNTRACK
                preserveMissMark = false;
                debugs(3, DBG_IMPORTANT, "WARNING: Squid not compiled with Netfilter conntrack library. "
                       << "Netfilter mark preservation not available.");
#endif // USE_LIBNETFILTERCONNTRACK
#elif SO_MARK // SO_MARK && USE_LIBCAP
                debugs(3, DBG_CRITICAL, "ERROR: Invalid parameter 'mark' in qos_flows option. "
                       << "Linux Netfilter marking not available without LIBCAP support.");
                self_destruct();
#else // SO_MARK && USE_LIBCAP
                debugs(3, DBG_CRITICAL, "ERROR: Invalid parameter 'mark' in qos_flows option. "
                       << "Linux Netfilter marking not available on this platform.");
                self_destruct();
#endif // SO_MARK && USE_LIBCAP
            } else if (strncmp(token, "tos",3) == 0) {
                preserveMissTos = true;
                tos = true;
            } else {
                preserveMissTos = true;
                tos = true;
            }
        }

        if (strncmp(token, "local-hit=",10) == 0) {

            if (mark) {
                if (!xstrtoui(&token[10], NULL, &markLocalHit, 0, std::numeric_limits<nfmark_t>::max())) {
                    debugs(3, DBG_CRITICAL, "ERROR: Bad mark local-hit value " << &token[10]);
                    self_destruct();
                }
            } else {
                unsigned int v = 0;
                if (!xstrtoui(&token[10], NULL, &v, 0, std::numeric_limits<tos_t>::max())) {
                    debugs(3, DBG_CRITICAL, "ERROR: Bad TOS local-hit value " << &token[10]);
                    self_destruct();
                }
                tosLocalHit = (tos_t)v;
            }

        } else if (strncmp(token, "sibling-hit=",12) == 0) {

            if (mark) {
                if (!xstrtoui(&token[12], NULL, &markSiblingHit, 0, std::numeric_limits<nfmark_t>::max())) {
                    debugs(3, DBG_CRITICAL, "ERROR: Bad mark sibling-hit value " << &token[12]);
                    self_destruct();
                }
            } else {
                unsigned int v = 0;
                if (!xstrtoui(&token[12], NULL, &v, 0, std::numeric_limits<tos_t>::max())) {
                    debugs(3, DBG_CRITICAL, "ERROR: Bad TOS sibling-hit value " << &token[12]);
                    self_destruct();
                }
                tosSiblingHit = (tos_t)v;
            }

        } else if (strncmp(token, "parent-hit=",11) == 0) {

            if (mark) {
                if (!xstrtoui(&token[11], NULL, &markParentHit, 0, std::numeric_limits<nfmark_t>::max())) {
                    debugs(3, DBG_CRITICAL, "ERROR: Bad mark parent-hit value " << &token[11]);
                    self_destruct();
                }
            } else {
                unsigned int v = 0;
                if (!xstrtoui(&token[11], NULL, &v, 0, std::numeric_limits<tos_t>::max())) {
                    debugs(3, DBG_CRITICAL, "ERROR: Bad TOS parent-hit value " << &token[11]);
                    self_destruct();
                }
                tosParentHit = (tos_t)v;
            }

        } else if (strncmp(token, "miss=",5) == 0) {

            char *end;
            if (mark) {
                if (!xstrtoui(&token[5], &end, &markMiss, 0, std::numeric_limits<nfmark_t>::max())) {
                    debugs(3, DBG_CRITICAL, "ERROR: Bad mark miss value " << &token[5]);
                    self_destruct();
                }
                if (*end == '/') {
                    if (!xstrtoui(end + 1, NULL, &markMissMask, 0, std::numeric_limits<nfmark_t>::max())) {
                        debugs(3, DBG_CRITICAL, "ERROR: Bad mark miss mask value " << (end + 1) << ". Using 0xFFFFFFFF instead.");
                        markMissMask = 0xFFFFFFFF;
                    }
                } else {
                    markMissMask = 0xFFFFFFFF;
                }
            } else {
                unsigned int v = 0;
                if (!xstrtoui(&token[5], &end, &v, 0, std::numeric_limits<tos_t>::max())) {
                    debugs(3, DBG_CRITICAL, "ERROR: Bad TOS miss value " << &token[5]);
                    self_destruct();
                }
                tosMiss = (tos_t)v;
                if (*end == '/') {
                    if (!xstrtoui(end + 1, NULL, &v, 0, std::numeric_limits<tos_t>::max())) {
                        debugs(3, DBG_CRITICAL, "ERROR: Bad TOS miss mask value " << (end + 1) << ". Using 0xFF instead.");
                        tosMissMask = 0xFF;
                    } else
                        tosMissMask = (tos_t)v;
                } else {
                    tosMissMask = 0xFF;
                }
            }

        } else if (strcmp(token, "disable-preserve-miss") == 0) {

            if (preserveMissTosMask!=0xFFU || preserveMissMarkMask!=0xFFFFFFFFU) {
                debugs(3, DBG_CRITICAL, "ERROR: miss-mask feature cannot be set with disable-preserve-miss");
                self_destruct();
            }
            if (mark) {
                preserveMissMark = false;
                preserveMissMarkMask = 0;
            } else {
                preserveMissTos = false;
                preserveMissTosMask = 0;
            }

        } else if (strncmp(token, "miss-mask=",10) == 0) {

            if (mark && preserveMissMark) {
                if (!xstrtoui(&token[10], NULL, &preserveMissMarkMask, 0, std::numeric_limits<nfmark_t>::max())) {
                    debugs(3, DBG_CRITICAL, "ERROR: Bad mark miss-mark value " << &token[10]);
                    self_destruct();
                }
            } else if (preserveMissTos) {
                unsigned int v = 0;
                if (!xstrtoui(&token[10], NULL, &v, 0, std::numeric_limits<tos_t>::max())) {
                    debugs(3, DBG_CRITICAL, "ERROR: Bad TOS miss-mark value " << &token[10]);
                    self_destruct();
                }
                preserveMissTosMask = (tos_t)v;
            } else {
                debugs(3, DBG_CRITICAL, "ERROR: miss-mask feature cannot be set without miss-preservation enabled");
                self_destruct();
            }

        }
    }
}
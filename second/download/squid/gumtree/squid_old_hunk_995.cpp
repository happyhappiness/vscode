        }
        storeAppendPrintf(sentry, "Currently established connections: %d\n",
                          c->n_established);
        storeAppendPrintf(sentry, "    ICP  Requests %d\n",
                          c->Icp.n_requests);

        for (LogTags l = LOG_TAG_NONE; l < LOG_TYPE_MAX; ++l) {
            if (c->Icp.result_hist[l] == 0)
                continue;

            icp_total += c->Icp.result_hist[l];

            if (LOG_UDP_HIT == l)
                icp_hits += c->Icp.result_hist[l];

            storeAppendPrintf(sentry, "        %-20.20s %7d %3d%%\n",LogTags_str[l], c->Icp.result_hist[l], Math::intPercent(c->Icp.result_hist[l], c->Icp.n_requests));
        }

        storeAppendPrintf(sentry, "    HTTP Requests %d\n", c->Http.n_requests);

        for (LogTags l = LOG_TAG_NONE; l < LOG_TYPE_MAX; ++l) {
            if (c->Http.result_hist[l] == 0)
                continue;

            http_total += c->Http.result_hist[l];

            if (logTypeIsATcpHit(l))
                http_hits += c->Http.result_hist[l];

            storeAppendPrintf(sentry,
                              "        %-20.20s %7d %3d%%\n",
                              LogTags_str[l],
                              c->Http.result_hist[l],
                              Math::intPercent(c->Http.result_hist[l], c->Http.n_requests));
        }

        storeAppendPrintf(sentry, "\n");
    }

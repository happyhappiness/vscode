
            icp_total += c->Icp.result_hist[l];

            if (LOG_UDP_HIT == l)
                icp_hits += c->Icp.result_hist[l];

            storeAppendPrintf(sentry, "        %-20.20s %7d %3d%%\n",Format::log_tags[l], c->Icp.result_hist[l], Math::intPercent(c->Icp.result_hist[l], c->Icp.n_requests));
        }

        storeAppendPrintf(sentry, "    HTTP Requests %d\n", c->Http.n_requests);

        for (l = LOG_TAG_NONE; l < LOG_TYPE_MAX; ++l) {
            if (c->Http.result_hist[l] == 0)

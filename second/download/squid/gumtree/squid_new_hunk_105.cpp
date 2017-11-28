
            if (logTypeIsATcpHit(l))
                http_hits += c->Http.result_hist[l];

            storeAppendPrintf(sentry,
                              "        %-20.20s %7d %3d%%\n",
                              Format::log_tags[l],
                              c->Http.result_hist[l],
                              Math::intPercent(c->Http.result_hist[l], c->Http.n_requests));
        }

        storeAppendPrintf(sentry, "\n");
    }

buf = sdscatprintf(buf,"%jd %d",
                    (intmax_t)server.saveparams[j].seconds,
                    server.saveparams[j].changes);
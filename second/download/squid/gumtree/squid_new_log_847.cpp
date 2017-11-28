storeAppendPrintf(sentry, "%#06x %4d %5d %10.3f %9.3f %c %s\n",
                          (int) q->query_id, (int) q->sz, q->nsends,
                          tvSubDsec(q->start_t, current_time),
                          tvSubDsec(q->sent_t, current_time),
                          (q->permit_mdns? 'M':' '),
                          q->name);
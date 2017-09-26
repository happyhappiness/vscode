        else if (c->bread != doclen) {
            bad++;
            err_length++;
        }
        /* save out time */
        if (done < requests) {
            struct data *s = &stats[done++];
            c->done      = lasttime = apr_time_now();
            s->starttime = c->start;
            s->ctime     = ap_max(0, c->connect - c->start);
            s->time      = ap_max(0, c->done - c->start);
            s->waittime  = ap_max(0, c->beginread - c->endwrite);
            if (heartbeatres && !(done % heartbeatres)) {
                fprintf(stderr, "Completed %d requests\n", done);
                fflush(stderr);
            }
        }
    }

    {
        apr_pollfd_t remove_pollfd;
        remove_pollfd.desc_type = APR_POLL_SOCKET;

        }
        else if (c->bread != doclen) {
            bad++;
            err_length++;
        }
        if (done < requests) {
            struct data s;
            doneka++;
            if (done && heartbeatres && !(done % heartbeatres)) {
                fprintf(stderr, "Completed %ld requests\n", done);
                fflush(stderr);
            }
            c->done = apr_time_now();
            s.read = c->read;
            s.starttime = c->start;
            s.ctime = ap_max(0, (c->connect - c->start) / 1000);
            s.waittime = ap_max(0, (c->beginread - c->endwrite) / 1000);
            s.time = ap_max(0, (c->done - c->start) / 1000);
            stats[done++] = s;
        }
        c->keepalive = 0;
        c->length = 0;
        c->gotheader = 0;
        c->cbx = 0;
        c->read = c->bread = 0;
        c->start = c->connect = apr_time_now(); /* zero connect time with keep-alive */
        write_request(c);
    }
}

/* --------------------------------------------------------- */

/* run the tests */

static void test(void)
{
    apr_time_t now;
    apr_int16_t rv;
    long i;
    apr_status_t status;
    int snprintf_res = 0;
#ifdef NOT_ASCII
    apr_size_t inbytes_left, outbytes_left;
#endif


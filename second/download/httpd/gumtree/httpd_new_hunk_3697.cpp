            ap_rputs("<table border=\"1\">\n", r);
            ap_rprintf(r, "<tr><td>Child pid:</td><td>%d</td></tr>\n",
                       (int) getpid());
            ap_rprintf(r, "<tr><td>Counter:</td><td>%u</td></tr>\n",
                       (unsigned int)base->counter);
            ap_rputs("</table>\n", r);
        }
        else {
            /*
             * Send a page saying that we couldn't get the lock. Don't say
             * what the counter is, because without the lock the value could
             * race.
             */
            ap_rprintf(r, "<p>Child %d failed to acquire lock "

                    new_pollfd.reqevents = APR_POLLIN;
                    new_pollfd.desc.s = c->aprsock;
                    new_pollfd.client_data = c;
                    apr_pollset_add(readbits, &new_pollfd);
                }
        }
    } while (lasttime < stoptime && done < requests);
    
    if (heartbeatres)
        fprintf(stderr, "Finished %d requests\n", done);
    else
        printf("..done\n");

    if (use_html)
        output_html_results();
    else
        output_results(0);
}

/* ------------------------------------------------------- */

/* display copyright information */
static void copyright(void)
{
    if (!use_html) {
        printf("This is ApacheBench, Version %s\n", AP_AB_BASEREVISION " <$Revision: 655654 $>");
        printf("Copyright 1996 Adam Twiss, Zeus Technology Ltd, http://www.zeustech.net/\n");
        printf("Licensed to The Apache Software Foundation, http://www.apache.org/\n");
        printf("\n");
    }
    else {
        printf("<p>\n");
        printf(" This is ApacheBench, Version %s <i>&lt;%s&gt;</i><br>\n", AP_AB_BASEREVISION, "$Revision: 655654 $");
        printf(" Copyright 1996 Adam Twiss, Zeus Technology Ltd, http://www.zeustech.net/<br>\n");
        printf(" Licensed to The Apache Software Foundation, http://www.apache.org/<br>\n");
        printf("</p>\n<p>\n");
    }
}

/* display usage information */
static void usage(const char *progname)
{
    fprintf(stderr, "Usage: %s [options] [http"
#ifdef USE_SSL
        "[s]"
#endif
        "://]hostname[:port]/path\n", progname);
/* 80 column ruler:  ********************************************************************************
 */
    fprintf(stderr, "Options are:\n");
    fprintf(stderr, "    -n requests     Number of requests to perform\n");
    fprintf(stderr, "    -c concurrency  Number of multiple requests to make\n");
    fprintf(stderr, "    -t timelimit    Seconds to max. wait for responses\n");
    fprintf(stderr, "    -b windowsize   Size of TCP send/receive buffer, in bytes\n");
    fprintf(stderr, "    -p postfile     File containing data to POST. Remember also to set -T\n");
    fprintf(stderr, "    -T content-type Content-type header for POSTing, eg.\n");
    fprintf(stderr, "                    'application/x-www-form-urlencoded'\n");
    fprintf(stderr, "                    Default is 'text/plain'\n");
    fprintf(stderr, "    -v verbosity    How much troubleshooting info to print\n");
    fprintf(stderr, "    -w              Print out results in HTML tables\n");
    fprintf(stderr, "    -i              Use HEAD instead of GET\n");
    fprintf(stderr, "    -x attributes   String to insert as table attributes\n");
    fprintf(stderr, "    -y attributes   String to insert as tr attributes\n");
    fprintf(stderr, "    -z attributes   String to insert as td or th attributes\n");

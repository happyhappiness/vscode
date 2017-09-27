            }
            else if (verbosity >= 3) {
                printf("LOG: Response code = %s\n", respcode);
            }
            c->gotheader = 1;
            *s = 0;     /* terminate at end of header */
            if (keepalive &&
            (strstr(c->cbuff, "Keep-Alive")
             || strstr(c->cbuff, "keep-alive"))) {  /* for benefit of MSIIS */
                char *cl;
                cl = strstr(c->cbuff, "Content-Length:");
                /* handle NCSA, which sends Content-length: */
                if (!cl)
                    cl = strstr(c->cbuff, "Content-length:");
                if (cl) {
                    c->keepalive = 1;
                    /* response to HEAD doesn't have entity body */
                    c->length = method != HEAD ? atoi(cl + 16) : 0;
                }
                /* The response may not have a Content-Length header */
                if (!cl) {
                    c->keepalive = 1;
                    c->length = 0;
                }
            }
            c->bread += c->cbx - (s + l - c->cbuff) + r - tocopy;
            totalbread += c->bread;
        }

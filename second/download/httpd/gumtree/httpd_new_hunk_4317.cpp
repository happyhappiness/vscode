            }
            else if (verbosity >= 3) {
                printf("LOG: Response code = %s\n", respcode);
            }
            c->gotheader = 1;
            *s = 0;     /* terminate at end of header */
            if (keepalive && xstrcasestr(c->cbuff, "Keep-Alive")) {
                char *cl;
                c->keepalive = 1;
                cl = xstrcasestr(c->cbuff, "Content-Length:");
                if (cl && method != HEAD) {
                    /* response to HEAD doesn't have entity body */
                    c->length = atoi(cl + 16);
                }
                else {
                    c->length = 0;
                }
            }
            c->bread += c->cbx - (s + l - c->cbuff) + r - tocopy;
            totalbread += c->bread;
        }

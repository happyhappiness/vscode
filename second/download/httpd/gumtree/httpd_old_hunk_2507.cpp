                    while (*p > 32)

                        *q++ = *p++;

                }

                *q = 0;

            }



            c->gotheader = 1;

            *s = 0;             /* terminate at end of header */

            if (keepalive &&

                (strstr(c->cbuff, "Keep-Alive")

                 || strstr(c->cbuff, "keep-alive"))) {  /* for benefit of MSIIS */

                char *cl;

                cl = strstr(c->cbuff, "Content-Length:");

                /* for cacky servers like NCSA which break the spec and send a 

                   lower case 'l' */

                if (!cl)

                    cl = strstr(c->cbuff, "Content-length:");

                if (cl) {

                    c->keepalive = 1;

                    c->length = atoi(cl + 16);

                }


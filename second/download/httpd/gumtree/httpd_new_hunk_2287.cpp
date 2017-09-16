                    while (*p > 32)

                        *q++ = *p++;

                }

                *q = 0;

            }



	    /* XXX: this parsing isn't even remotely HTTP compliant...

	     * but in the interest of speed it doesn't totally have to be,

	     * it just needs to be extended to handle whatever servers

	     * folks want to test against. -djg */



            /* check response code */

            part = strstr(c->cbuff, "HTTP");                /* really HTTP/1.x_ */

            strncpy(respcode, (part+strlen("HTTP/1.x_")), 3);

	    respcode[3] = '\0';

            if (respcode[0] != '2') {

                err_response++;

                if (verbosity >= 2) printf ("WARNING: Response code not 2xx (%s)\n", respcode);

            }

	    else if (verbosity >= 3) {

                printf("LOG: Response code = %s\n", respcode);

            }



            c->gotheader = 1;

            *s = 0;             /* terminate at end of header */

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

                    c->length = atoi(cl + 16);

                }


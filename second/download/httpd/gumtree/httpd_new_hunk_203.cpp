                 "An appropriate representation of the requested resource ",

                          ap_escape_html(r->pool, r->uri),

                          " could not be found on this server.<P>\n", NULL);

                /* fall through */

            case MULTIPLE_CHOICES:

                {

                    const char *list;

                    if ((list = ap_table_get(r->notes, "variant-list")))

                        ap_bputs(list, fd);

                }

                break;

            case LENGTH_REQUIRED:

                ap_bvputs(fd, "A request of the requested method ", r->method,

++ apache_1.3.1/src/main/http_request.c	1998-07-02 05:19:54.000000000 +0800


        additional = atoi(&code[1]);

        break;

    default:

        /* expecting the add_* routines to be case-hardened this 

         * is just a reminder that module is beta

         */

        ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,

                    "internal error: bad expires code: %s", r->filename);

        return SERVER_ERROR;

    };



    expires = base + additional;

    ap_snprintf(age, sizeof(age), "max-age=%d", (int) expires - (int) r->request_time);

-- apache_1.3.1/src/modules/standard/mod_imap.c	1998-07-09 01:47:15.000000000 +0800


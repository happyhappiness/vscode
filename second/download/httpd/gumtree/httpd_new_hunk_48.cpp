            else

                *tlength += 4 + strlen(r->boundary) + 4;

        }

        return 0;

    }



    range = ap_getword(r->pool, r_range, ',');

    if (!parse_byterange(range, r->clength, &range_start, &range_end))

        /* Skip this one */

        return internal_byterange(realreq, tlength, r, r_range, offset,

                                  length);



    if (r->byterange > 1) {

        const char *ct = r->content_type ? r->content_type : ap_default_type(r);

        char ts[MAX_STRING_LEN];



        ap_snprintf(ts, sizeof(ts), "%ld-%ld/%ld", range_start, range_end,

                    r->clength);

        if (realreq)

            ap_rvputs(r, "\015\012--", r->boundary, "\015\012Content-type: ",


static void do_headers_fixup(request_rec *r, apr_table_t *headers,
                             apr_array_header_t *fixup, int early)
{
    int i;

    for (i = 0; i < fixup->nelts; ++i) {
        header_entry *hdr = &((header_entry *) (fixup->elts))[i];
        const char *envar = hdr->condition_var;

        /* ignore early headers in late calls */
        if (!early && (envar == condition_early)) {
            continue;
        }
        /* ignore late headers in early calls */
        else if (early && (envar != condition_early)) {
            continue;
        }
        /* Have any conditional envar-controlled Header processing to do? */
        else if (envar && !early) {
            if (*envar != '!') {
                if (apr_table_get(r->subprocess_env, envar) == NULL)
                    continue;
            }
            else {
                if (apr_table_get(r->subprocess_env, &envar[1]) != NULL)
                    continue;
            }
        }

        switch (hdr->action) {
        case hdr_add:
            apr_table_addn(headers, hdr->header, process_tags(hdr, r));
            break;
        case hdr_append:
            apr_table_mergen(headers, hdr->header, process_tags(hdr, r));
            break;
        case hdr_set:
            apr_table_setn(headers, hdr->header, process_tags(hdr, r));
            break;
        case hdr_unset:
            apr_table_unset(headers, hdr->header);
            break;
        case hdr_echo:
        {
            echo_do v;
            v.r = r;
            v.hdr = hdr;
            apr_table_do((int (*) (void *, const char *, const char *))
                         echo_header, (void *) &v, r->headers_in, NULL);
            break;
        }
        }
    }
}
        else if (!(match = apr_table_get(r->headers_out, "Last-Modified"))
                 || (strcmp(if_range, match) != 0)) {
            return 0;
        }
    }

    if (!ap_strchr_c(range, ',')) {
        /* a single range */
        num_ranges = 1;
    }
    else {
        /* a multiple range */
        num_ranges = 2;
    }

    r->status = HTTP_PARTIAL_CONTENT;
    r->range = range + 6;

    return num_ranges;
}

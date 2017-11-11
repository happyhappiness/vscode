static void set_neg_headers(request_rec *r, negotiation_state *neg,
                            int alg_result)
{
    apr_table_t *hdrs;
    var_rec *avail_recs = (var_rec *) neg->avail_vars->elts;
    const char *sample_type = NULL;
    const char *sample_language = NULL;
    const char *sample_encoding = NULL;
    const char *sample_charset = NULL;
    char *lang;
    char *qstr;
    char *lenstr;
    apr_off_t len;
    apr_array_header_t *arr;
    int max_vlist_array = (neg->avail_vars->nelts * 21);
    int first_variant = 1;
    int vary_by_type = 0;
    int vary_by_language = 0;
    int vary_by_charset = 0;
    int vary_by_encoding = 0;
    int j;

    /* In order to avoid O(n^2) memory copies in building Alternates,
     * we preallocate a apr_table_t with the maximum substrings possible,
     * fill it with the variant list, and then concatenate the entire array.
     * Note that if you change the number of substrings pushed, you also
     * need to change the calculation of max_vlist_array above.
     */
    if (neg->send_alternates && neg->avail_vars->nelts)
        arr = apr_array_make(r->pool, max_vlist_array, sizeof(char *));
    else
        arr = NULL;

    /* Put headers into err_headers_out, since send_http_header()
     * outputs both headers_out and err_headers_out.
     */
    hdrs = r->err_headers_out;

    for (j = 0; j < neg->avail_vars->nelts; ++j) {
        var_rec *variant = &avail_recs[j];

        if (variant->content_languages && variant->content_languages->nelts) {
            lang = apr_array_pstrcat(r->pool, variant->content_languages, ',');
        }
        else {
            lang = NULL;
        }

        /* Calculate Vary by looking for any difference between variants */

        if (first_variant) {
            sample_type     = variant->mime_type;
            sample_charset  = variant->content_charset;
            sample_language = lang;
            sample_encoding = variant->content_encoding;
        }
        else {
            if (!vary_by_type &&
                strcmp(sample_type ? sample_type : "", 
                       variant->mime_type ? variant->mime_type : "")) {
                vary_by_type = 1;
            }
            if (!vary_by_charset &&
                strcmp(sample_charset ? sample_charset : "",
                       variant->content_charset ?
                       variant->content_charset : "")) {
                vary_by_charset = 1;
            }
            if (!vary_by_language &&
                strcmp(sample_language ? sample_language : "", 
                       lang ? lang : "")) {
                vary_by_language = 1;
            }
            if (!vary_by_encoding &&
                strcmp(sample_encoding ? sample_encoding : "",
                       variant->content_encoding ? 
                       variant->content_encoding : "")) {
                vary_by_encoding = 1;
            }
        }
        first_variant = 0;

        if (!neg->send_alternates)
            continue;

        /* Generate the string components for this Alternates entry */

        *((const char **) apr_array_push(arr)) = "{\"";
        *((const char **) apr_array_push(arr)) = variant->file_name;
        *((const char **) apr_array_push(arr)) = "\" ";

        qstr = (char *) apr_palloc(r->pool, 6);
        apr_snprintf(qstr, 6, "%1.3f", variant->source_quality);

        /* Strip trailing zeros (saves those valuable network bytes) */
        if (qstr[4] == '0') {
            qstr[4] = '\0';
            if (qstr[3] == '0') {
                qstr[3] = '\0';
                if (qstr[2] == '0') {
                    qstr[1] = '\0';
                }
            }
        }
        *((const char **) apr_array_push(arr)) = qstr;

        if (variant->mime_type && *variant->mime_type) {
            *((const char **) apr_array_push(arr)) = " {type ";
            *((const char **) apr_array_push(arr)) = variant->mime_type;
            *((const char **) apr_array_push(arr)) = "}";
        }
        if (variant->content_charset && *variant->content_charset) {
            *((const char **) apr_array_push(arr)) = " {charset ";
            *((const char **) apr_array_push(arr)) = variant->content_charset;
            *((const char **) apr_array_push(arr)) = "}";
        }
        if (lang) {
            *((const char **) apr_array_push(arr)) = " {language ";
            *((const char **) apr_array_push(arr)) = lang;
            *((const char **) apr_array_push(arr)) = "}";
        }
        if (variant->content_encoding && *variant->content_encoding) {
            /* Strictly speaking, this is non-standard, but so is TCN */

            *((const char **) apr_array_push(arr)) = " {encoding ";
            *((const char **) apr_array_push(arr)) = variant->content_encoding;
            *((const char **) apr_array_push(arr)) = "}";
        }

        /* Note that the Alternates specification (in rfc2295) does
         * not require that we include {length x}, so we could omit it
         * if determining the length is too expensive.  We currently
         * always include it though.  22 bytes is enough for 2^64.
         *
         * If the variant is a CGI script, find_content_length would
         * return the length of the script, not the output it
         * produces, so we check for the presence of a handler and if
         * there is one we don't add a length.
         * 
         * XXX: TODO: This check does not detect a CGI script if we
         * get the variant from a type map.  This needs to be fixed
         * (without breaking things if the type map specifies a
         * content-length, which currently leads to the correct result).
         */
        if (!(variant->sub_req && variant->sub_req->handler)
            && (len = find_content_length(neg, variant)) >= 0) {

            lenstr = (char *) apr_palloc(r->pool, 22);
            apr_snprintf(lenstr, 22, "%" APR_OFF_T_FMT, len);
            *((const char **) apr_array_push(arr)) = " {length ";
            *((const char **) apr_array_push(arr)) = lenstr;
            *((const char **) apr_array_push(arr)) = "}";
        }
      
        *((const char **) apr_array_push(arr)) = "}";
        *((const char **) apr_array_push(arr)) = ", "; /* trimmed below */
    }

    if (neg->send_alternates && neg->avail_vars->nelts) {
        arr->nelts--;                                 /* remove last comma */
        apr_table_mergen(hdrs, "Alternates",
                        apr_array_pstrcat(r->pool, arr, '\0'));
    } 

    if (neg->is_transparent || vary_by_type || vary_by_language ||
        vary_by_language || vary_by_charset || vary_by_encoding) {

        apr_table_mergen(hdrs, "Vary", 2 + apr_pstrcat(r->pool,
            neg->is_transparent ? ", negotiate"       : "",
            vary_by_type        ? ", accept"          : "",
            vary_by_language    ? ", accept-language" : "",
            vary_by_charset     ? ", accept-charset"  : "",
            vary_by_encoding    ? ", accept-encoding" : "", NULL));
    }

    if (neg->is_transparent) { /* Create TCN response header */
        apr_table_setn(hdrs, "TCN",
                      alg_result == alg_list ? "list" : "choice");
    }
}
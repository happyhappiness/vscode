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
        *((const char **) apr_array_push(arr)) = ap_escape_path_segment(r->pool, variant->file_name);
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
        
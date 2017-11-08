static char *make_variant_list(request_rec *r, negotiation_state *neg)
{
    apr_array_header_t *arr;
    int i;
    int max_vlist_array = (neg->avail_vars->nelts * 15) + 2;

    /* In order to avoid O(n^2) memory copies in building the list,
     * we preallocate a apr_table_t with the maximum substrings possible,
     * fill it with the variant list, and then concatenate the entire array.
     */
    arr = apr_array_make(r->pool, max_vlist_array, sizeof(char *));

    *((const char **) apr_array_push(arr)) = "Available variants:\n<ul>\n";

    for (i = 0; i < neg->avail_vars->nelts; ++i) {
        var_rec *variant = &((var_rec *) neg->avail_vars->elts)[i];
        const char *filename = variant->file_name ? variant->file_name : "";
        apr_array_header_t *languages = variant->content_languages;
        const char *description = variant->description
                                    ? variant->description
                                    : "";

        /* The format isn't very neat, and it would be nice to make
         * the tags human readable (eg replace 'language en' with 'English').
         * Note that if you change the number of substrings pushed, you also
         * need to change the calculation of max_vlist_array above.
         */
        *((const char **) apr_array_push(arr)) = "<li><a href=\"";
        *((const char **) apr_array_push(arr)) = ap_escape_path_segment(r->pool, filename);
        *((const char **) apr_array_push(arr)) = "\">";
        *((const char **) apr_array_push(arr)) = ap_escape_html(r->pool, filename);
        *((const char **) apr_array_push(arr)) = "</a> ";
        *((const char **) apr_array_push(arr)) = description;

        if (variant->mime_type && *variant->mime_type) {
            *((const char **) apr_array_push(arr)) = ", type ";
            *((const char **) apr_array_push(arr)) = variant->mime_type;
        }
        if (languages && languages->nelts) {
            *((const char **) apr_array_push(arr)) = ", language ";
            *((const char **) apr_array_push(arr)) = apr_array_pstrcat(r->pool,
                                                       languages, ',');
        }
        if (variant->content_charset && *variant->content_charset) {
            *((const char **) apr_array_push(arr)) = ", charset ";
            *((const char **) apr_array_push(arr)) = variant->content_charset;
        }
        if (variant->content_encoding) {
            *((const char **) apr_array_push(arr)) = ", encoding ";
            *((const char **) apr_array_push(arr)) = variant->content_encoding;
        }
        *((const char **) apr_array_push(arr)) = "</li>\n";
    }
    *((const char **) apr_array_push(arr)) = "</ul>\n";

    return apr_array_pstrcat(r->pool, arr, '\0');
}
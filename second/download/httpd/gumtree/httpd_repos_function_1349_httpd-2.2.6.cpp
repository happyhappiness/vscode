static void fixup_vary(request_rec *r)
{
    apr_array_header_t *varies;

    varies = apr_array_make(r->pool, 5, sizeof(char *));

    /* Extract all Vary fields from the headers_out, separate each into
     * its comma-separated fieldname values, and then add them to varies
     * if not already present in the array.
     */
    apr_table_do((int (*)(void *, const char *, const char *))uniq_field_values,
                 (void *) varies, r->headers_out, "Vary", NULL);

    /* If we found any, replace old Vary fields with unique-ified value */

    if (varies->nelts > 0) {
        apr_table_setn(r->headers_out, "Vary",
                       apr_array_pstrcat(r->pool, varies, ','));
    }
}
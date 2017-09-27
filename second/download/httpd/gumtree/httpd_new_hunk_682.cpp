     * the headers out (including the Allow header)
     */

    return OK;
}

AP_DECLARE(void) ap_set_content_type(request_rec *r, const char *ct)
{
    if (!ct) {
        r->content_type = NULL;
    }
    else if (!r->content_type || strcmp(r->content_type, ct)) {
        r->content_type = ct;

        /* Insert filters requested by the AddOutputFiltersByType
         * configuration directive. Content-type filters must be
         * inserted after the content handlers have run because
         * only then, do we reliably know the content-type.
         */
        ap_add_output_filters_by_type(r);
    }
}

static const char *add_optional_notes(request_rec *r,
                                      const char *prefix,
                                      const char *key,
                                      const char *suffix)
{
    const char *notes, *result;

    if ((notes = apr_table_get(r->notes, key)) == NULL) {
        result = apr_pstrcat(r->pool, prefix, suffix, NULL);
    }
    else {
        result = apr_pstrcat(r->pool, prefix, notes, suffix, NULL);
    }

    return result;
}

/* construct and return the default error message for a given
 * HTTP defined error code
 */
static const char *get_canned_error_string(int status,

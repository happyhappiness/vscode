static int dav_meets_conditions(request_rec *r, int resource_state)
{
    const char *if_match, *if_none_match;
    int retVal;

    /* If-Match '*' fix. Resource existence not checked by ap_meets_conditions.
     * If-Match '*' request should succeed only if the resource exists. */
    if ((if_match = apr_table_get(r->headers_in, "If-Match")) != NULL) {
        if (if_match[0] == '*' && resource_state != DAV_RESOURCE_EXISTS)
            return HTTP_PRECONDITION_FAILED;
    }

    retVal = ap_meets_conditions(r);

    /* If-None-Match '*' fix. If-None-Match '*' request should succeed 
     * if the resource does not exist. */
    if (retVal == HTTP_PRECONDITION_FAILED) {
        /* Note. If if_none_match != NULL, if_none_match is the culprit.
         * Since, in presence of If-None-Match, 
         * other If-* headers are undefined. */
        if ((if_none_match =
            apr_table_get(r->headers_in, "If-None-Match")) != NULL) {
            if (if_none_match[0] == '*'
                && resource_state != DAV_RESOURCE_EXISTS) {
                return OK;
            }
        }
    }

    return retVal;
}
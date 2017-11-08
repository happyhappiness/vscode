static int uri_meets_conditions(const apr_uri_t *filter, const int pathlen,
                                const apr_uri_t *url)
{

    /* Scheme, hostname port and local part. The filter URI and the
     * URI we test may have the following shapes:
     *   /<path>
     *   <scheme>[:://<hostname>[:<port>][/<path>]]
     * That is, if there is no scheme then there must be only the path,
     * and we check only the path; if there is a scheme, we check the
     * scheme for equality, and then if present we match the hostname,
     * and then if present match the port, and finally the path if any.
     *
     * Note that this means that "/<path>" only matches local paths,
     * and to match proxied paths one *must* specify the scheme.
     */

    /* Is the filter is just for a local path or a proxy URI? */
    if (!filter->scheme) {
        if (url->scheme || url->hostname) {
            return 0;
        }
    }
    else {
        /* The URI scheme must be present and identical except for case. */
        if (!url->scheme || strcasecmp(filter->scheme, url->scheme)) {
            return 0;
        }

        /* If the filter hostname is null or empty it matches any hostname,
         * if it begins with a "*" it matches the _end_ of the URI hostname
         * excluding the "*", if it begins with a "." it matches the _end_
         * of the URI * hostname including the ".", otherwise it must match
         * the URI hostname exactly. */

        if (filter->hostname && filter->hostname[0]) {
            if (filter->hostname[0] == '.') {
                const size_t fhostlen = strlen(filter->hostname);
                const size_t uhostlen = url->hostname ? strlen(url->hostname) : 0;

                if (fhostlen > uhostlen
                    || (url->hostname
                        && strcasecmp(filter->hostname,
                                      url->hostname + uhostlen - fhostlen))) {
                    return 0;
                }
            }
            else if (filter->hostname[0] == '*') {
                const size_t fhostlen = strlen(filter->hostname + 1);
                const size_t uhostlen = url->hostname ? strlen(url->hostname) : 0;

                if (fhostlen > uhostlen
                    || (url->hostname
                        && strcasecmp(filter->hostname + 1,
                                      url->hostname + uhostlen - fhostlen))) {
                    return 0;
                }
            }
            else if (!url->hostname || strcasecmp(filter->hostname, url->hostname)) {
                return 0;
            }
        }

        /* If the filter port is empty it matches any URL port.
         * If the filter or URL port are missing, or the URL port is
         * empty, they default to the port for their scheme. */

        if (!(filter->port_str && !filter->port_str[0])) {
            /* NOTE:  ap_port_of_scheme will return 0 if given NULL input */
            const unsigned fport = filter->port_str ? filter->port
                    : apr_uri_port_of_scheme(filter->scheme);
            const unsigned uport = (url->port_str && url->port_str[0])
                    ? url->port : apr_uri_port_of_scheme(url->scheme);

            if (fport != uport) {
                return 0;
            }
        }
    }

    /* For HTTP caching purposes, an empty (NULL) path is equivalent to
     * a single "/" path. RFCs 3986/2396
     */
    if (!url->path) {
        if (*filter->path == '/' && pathlen == 1) {
            return 1;
        }
        else {
            return 0;
        }
    }

    /* Url has met all of the filter conditions so far, determine
     * if the paths match.
     */
    return !strncmp(filter->path, url->path, pathlen);
}
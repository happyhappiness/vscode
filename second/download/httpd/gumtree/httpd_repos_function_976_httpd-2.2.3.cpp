static int uri_meets_conditions(apr_uri_t filter, int pathlen, apr_uri_t url)
{
    /* Compare the hostnames */
    if(filter.hostname) {
        if (!url.hostname) {
            return 0;
        }
        else if (strcasecmp(filter.hostname, url.hostname)) {
            return 0;
        }
    }

    /* Compare the schemes */
    if(filter.scheme) {
        if (!url.scheme) {
            return 0;
        }
        else if (strcasecmp(filter.scheme, url.scheme)) {
            return 0;
        }
    }

    /* Compare the ports */
    if(filter.port_str) {
        if (url.port_str && filter.port != url.port) {
            return 0;
        }
        /* NOTE:  ap_port_of_scheme will return 0 if given NULL input */
        else if (filter.port != apr_uri_port_of_scheme(url.scheme)) {
            return 0;
        }
    }
    else if(url.port_str && filter.scheme) {
        if (apr_uri_port_of_scheme(filter.scheme) == url.port) {
            return 0;
        }
    }

    /* Url has met all of the filter conditions so far, determine
     * if the paths match.
     */
    return !strncmp(filter.path, url.path, pathlen);
}
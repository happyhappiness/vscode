static const char *get_canned_error_string(int status,
                                           request_rec *r,
                                           const char *location)
{
    apr_pool_t *p = r->pool;
    const char *error_notes, *h1, *s1;

    switch (status) {
    case HTTP_MOVED_PERMANENTLY:
    case HTTP_MOVED_TEMPORARILY:
    case HTTP_TEMPORARY_REDIRECT:
        return(apr_pstrcat(p,
                           "<p>The document has moved <a href=\"",
                           ap_escape_html(r->pool, location),
                           "\">here</a>.</p>\n",
                           NULL));
    case HTTP_SEE_OTHER:
        return(apr_pstrcat(p,
                           "<p>The answer to your request is located "
                           "<a href=\"",
                           ap_escape_html(r->pool, location),
                           "\">here</a>.</p>\n",
                           NULL));
    case HTTP_USE_PROXY:
        return(apr_pstrcat(p,
                           "<p>This resource is only accessible "
                           "through the proxy\n",
                           ap_escape_html(r->pool, location),
                           "<br />\nYou will need to configure "
                           "your client to use that proxy.</p>\n",
                           NULL));
    case HTTP_PROXY_AUTHENTICATION_REQUIRED:
    case HTTP_UNAUTHORIZED:
        return("<p>This server could not verify that you\n"
               "are authorized to access the document\n"
               "requested.  Either you supplied the wrong\n"
               "credentials (e.g., bad password), or your\n"
               "browser doesn't understand how to supply\n"
               "the credentials required.</p>\n");
    case HTTP_BAD_REQUEST:
        return(add_optional_notes(r,
                                  "<p>Your browser sent a request that "
                                  "this server could not understand.<br />\n",
                                  "error-notes",
                                  "</p>\n"));
    case HTTP_FORBIDDEN:
        return(apr_pstrcat(p,
                           "<p>You don't have permission to access ",
                           ap_escape_html(r->pool, r->uri),
                           "\non this server.</p>\n",
                           NULL));
    case HTTP_NOT_FOUND:
        return(apr_pstrcat(p,
                           "<p>The requested URL ",
                           ap_escape_html(r->pool, r->uri),
                           " was not found on this server.</p>\n",
                           NULL));
    case HTTP_METHOD_NOT_ALLOWED:
        return(apr_pstrcat(p,
                           "<p>The requested method ", r->method,
                           " is not allowed for the URL ",
                           ap_escape_html(r->pool, r->uri),
                           ".</p>\n",
                           NULL));
    case HTTP_NOT_ACCEPTABLE:
        s1 = apr_pstrcat(p,
                         "<p>An appropriate representation of the "
                         "requested resource ",
                         ap_escape_html(r->pool, r->uri),
                         " could not be found on this server.</p>\n",
                         NULL);
        return(add_optional_notes(r, s1, "variant-list", ""));
    case HTTP_MULTIPLE_CHOICES:
        return(add_optional_notes(r, "", "variant-list", ""));
    case HTTP_LENGTH_REQUIRED:
        s1 = apr_pstrcat(p,
                         "<p>A request of the requested method ",
                         r->method,
                         " requires a valid Content-length.<br />\n",
                         NULL);
        return(add_optional_notes(r, s1, "error-notes", "</p>\n"));
    case HTTP_PRECONDITION_FAILED:
        return(apr_pstrcat(p,
                           "<p>The precondition on the request "
                           "for the URL ",
                           ap_escape_html(r->pool, r->uri),
                           " evaluated to false.</p>\n",
                           NULL));
    case HTTP_NOT_IMPLEMENTED:
        s1 = apr_pstrcat(p,
                         "<p>",
                         ap_escape_html(r->pool, r->method), " to ",
                         ap_escape_html(r->pool, r->uri),
                         " not supported.<br />\n",
                         NULL);
        return(add_optional_notes(r, s1, "error-notes", "</p>\n"));
    case HTTP_BAD_GATEWAY:
        s1 = "<p>The proxy server received an invalid" CRLF
            "response from an upstream server.<br />" CRLF;
        return(add_optional_notes(r, s1, "error-notes", "</p>\n"));
    case HTTP_VARIANT_ALSO_VARIES:
        return(apr_pstrcat(p,
                           "<p>A variant for the requested "
                           "resource\n<pre>\n",
                           ap_escape_html(r->pool, r->uri),
                           "\n</pre>\nis itself a negotiable resource. "
                           "This indicates a configuration error.</p>\n",
                           NULL));
    case HTTP_REQUEST_TIME_OUT:
        return("<p>Server timeout waiting for the HTTP request from the client.</p>\n");
    case HTTP_GONE:
        return(apr_pstrcat(p,
                           "<p>The requested resource<br />",
                           ap_escape_html(r->pool, r->uri),
                           "<br />\nis no longer available on this server "
                           "and there is no forwarding address.\n"
                           "Please remove all references to this "
                           "resource.</p>\n",
                           NULL));
    case HTTP_REQUEST_ENTITY_TOO_LARGE:
        return(apr_pstrcat(p,
                           "The requested resource<br />",
                           ap_escape_html(r->pool, r->uri), "<br />\n",
                           "does not allow request data with ",
                           r->method,
                           " requests, or the amount of data provided in\n"
                           "the request exceeds the capacity limit.\n",
                           NULL));
    case HTTP_REQUEST_URI_TOO_LARGE:
        s1 = "<p>The requested URL's length exceeds the capacity\n"
             "limit for this server.<br />\n";
        return(add_optional_notes(r, s1, "error-notes", "</p>\n"));
    case HTTP_UNSUPPORTED_MEDIA_TYPE:
        return("<p>The supplied request data is not in a format\n"
               "acceptable for processing by this resource.</p>\n");
    case HTTP_RANGE_NOT_SATISFIABLE:
        return("<p>None of the range-specifier values in the Range\n"
               "request-header field overlap the current extent\n"
               "of the selected resource.</p>\n");
    case HTTP_EXPECTATION_FAILED:
        return(apr_pstrcat(p,
                           "<p>The expectation given in the Expect "
                           "request-header"
                           "\nfield could not be met by this server.</p>\n"
                           "<p>The client sent<pre>\n    Expect: ",
                           apr_table_get(r->headers_in, "Expect"),
                           "\n</pre>\n"
                           "but we only allow the 100-continue "
                           "expectation.</p>\n",
                           NULL));
    case HTTP_UNPROCESSABLE_ENTITY:
        return("<p>The server understands the media type of the\n"
               "request entity, but was unable to process the\n"
               "contained instructions.</p>\n");
    case HTTP_LOCKED:
        return("<p>The requested resource is currently locked.\n"
               "The lock must be released or proper identification\n"
               "given before the method can be applied.</p>\n");
    case HTTP_FAILED_DEPENDENCY:
        return("<p>The method could not be performed on the resource\n"
               "because the requested action depended on another\n"
               "action and that other action failed.</p>\n");
    case HTTP_INSUFFICIENT_STORAGE:
        return("<p>The method could not be performed on the resource\n"
               "because the server is unable to store the\n"
               "representation needed to successfully complete the\n"
               "request.  There is insufficient free space left in\n"
               "your storage allocation.</p>\n");
    case HTTP_SERVICE_UNAVAILABLE:
        return("<p>The server is temporarily unable to service your\n"
               "request due to maintenance downtime or capacity\n"
               "problems. Please try again later.</p>\n");
    case HTTP_GATEWAY_TIME_OUT:
        return("<p>The proxy server did not receive a timely response\n"
               "from the upstream server.</p>\n");
    case HTTP_NOT_EXTENDED:
        return("<p>A mandatory extension policy in the request is not\n"
               "accepted by the server for this resource.</p>\n");
    default:                    /* HTTP_INTERNAL_SERVER_ERROR */
        /*
         * This comparison to expose error-notes could be modified to
         * use a configuration directive and export based on that
         * directive.  For now "*" is used to designate an error-notes
         * that is totally safe for any user to see (ie lacks paths,
         * database passwords, etc.)
         */
        if (((error_notes = apr_table_get(r->notes,
                                          "error-notes")) != NULL)
            && (h1 = apr_table_get(r->notes, "verbose-error-to")) != NULL
            && (strcmp(h1, "*") == 0)) {
            return(apr_pstrcat(p, error_notes, "<p />\n", NULL));
        }
        else {
            return(apr_pstrcat(p,
                               "<p>The server encountered an internal "
                               "error or\n"
                               "misconfiguration and was unable to complete\n"
                               "your request.</p>\n"
                               "<p>Please contact the server "
                               "administrator,\n ",
                               ap_escape_html(r->pool,
                                              r->server->server_admin),
                               " and inform them of the time the "
                               "error occurred,\n"
                               "and anything you might have done that "
                               "may have\n"
                               "caused the error.</p>\n"
                               "<p>More information about this error "
                               "may be available\n"
                               "in the server error log.</p>\n",
                               NULL));
        }
        /*
         * It would be nice to give the user the information they need to
         * fix the problem directly since many users don't have access to
         * the error_log (think University sites) even though they can easily
         * get this error by misconfiguring an htaccess file.  However, the
         * e error notes tend to include the real file pathname in this case,
         * which some people consider to be a breach of privacy.  Until we
         * can figure out a way to remove the pathname, leave this commented.
         *
         * if ((error_notes = apr_table_get(r->notes,
         *                                  "error-notes")) != NULL) {
         *     return(apr_pstrcat(p, error_notes, "<p />\n", NULL);
         * }
         * else {
         *     return "";
         * }
         */
    }
}
const char *
httpStatusString(http_status status)
{
    /* why not to return matching string instead of using "p" ? @?@ */
    const char *p = NULL;

    switch (status) {

    case 0:
        p = "Init";		/* we init .status with code 0 */
        break;

    case HTTP_CONTINUE:
        p = "Continue";
        break;

    case HTTP_SWITCHING_PROTOCOLS:
        p = "Switching Protocols";
        break;

    case HTTP_OK:
        p = "OK";
        break;

    case HTTP_CREATED:
        p = "Created";
        break;

    case HTTP_ACCEPTED:
        p = "Accepted";
        break;

    case HTTP_NON_AUTHORITATIVE_INFORMATION:
        p = "Non-Authoritative Information";
        break;

    case HTTP_NO_CONTENT:
        p = "No Content";
        break;

    case HTTP_RESET_CONTENT:
        p = "Reset Content";
        break;

    case HTTP_PARTIAL_CONTENT:
        p = "Partial Content";
        break;

    case HTTP_MULTI_STATUS:
        p = "Multi-Status";
        break;

    case HTTP_MULTIPLE_CHOICES:
        p = "Multiple Choices";
        break;

    case HTTP_MOVED_PERMANENTLY:
        p = "Moved Permanently";
        break;

    case HTTP_MOVED_TEMPORARILY:
        p = "Moved Temporarily";
        break;

    case HTTP_SEE_OTHER:
        p = "See Other";
        break;

    case HTTP_NOT_MODIFIED:
        p = "Not Modified";
        break;

    case HTTP_USE_PROXY:
        p = "Use Proxy";
        break;

    case HTTP_TEMPORARY_REDIRECT:
        p = "Temporary Redirect";
        break;

    case HTTP_PERMANENT_REDIRECT:
        p = "Permanent Redirect";
        break;

    case HTTP_BAD_REQUEST:
        p = "Bad Request";
        break;

    case HTTP_UNAUTHORIZED:
        p = "Unauthorized";
        break;

    case HTTP_PAYMENT_REQUIRED:
        p = "Payment Required";
        break;

    case HTTP_FORBIDDEN:
        p = "Forbidden";
        break;

    case HTTP_NOT_FOUND:
        p = "Not Found";
        break;

    case HTTP_METHOD_NOT_ALLOWED:
        p = "Method Not Allowed";
        break;

    case HTTP_NOT_ACCEPTABLE:
        p = "Not Acceptable";
        break;

    case HTTP_PROXY_AUTHENTICATION_REQUIRED:
        p = "Proxy Authentication Required";
        break;

    case HTTP_REQUEST_TIMEOUT:
        p = "Request Time-out";
        break;

    case HTTP_CONFLICT:
        p = "Conflict";
        break;

    case HTTP_GONE:
        p = "Gone";
        break;

    case HTTP_LENGTH_REQUIRED:
        p = "Length Required";
        break;

    case HTTP_PRECONDITION_FAILED:
        p = "Precondition Failed";
        break;

    case HTTP_REQUEST_ENTITY_TOO_LARGE:
        p = "Request Entity Too Large";
        break;

    case HTTP_REQUEST_URI_TOO_LARGE:
        p = "Request-URI Too Large";
        break;

    case HTTP_UNSUPPORTED_MEDIA_TYPE:
        p = "Unsupported Media Type";
        break;

    case HTTP_REQUESTED_RANGE_NOT_SATISFIABLE:
        p = "Requested Range Not Satisfiable";
        break;

    case HTTP_EXPECTATION_FAILED:
        p = "Expectation Failed";
        break;

    case HTTP_INTERNAL_SERVER_ERROR:
        p = "Internal Server Error";
        break;

    case HTTP_NOT_IMPLEMENTED:
        p = "Not Implemented";
        break;

    case HTTP_BAD_GATEWAY:
        p = "Bad Gateway";
        break;

    case HTTP_SERVICE_UNAVAILABLE:
        p = "Service Unavailable";
        break;

    case HTTP_GATEWAY_TIMEOUT:
        p = "Gateway Time-out";
        break;

    case HTTP_HTTP_VERSION_NOT_SUPPORTED:
        p = "HTTP Version not supported";
        break;

        // RFC 6585
    case HTTP_PRECONDITION_REQUIRED: // 428
        p = "Precondition Required";
        break;

    case HTTP_TOO_MANY_REQUESTS: // 429
        p = "Too Many Requests";
        break;

    case HTTP_REQUEST_HEADER_FIELDS_TOO_LARGE: // 431
        p = "Request Header Fields Too Large";
        break;

    case HTTP_NETWORK_AUTHENTICATION_REQUIRED: // 511
        p = "Network Authentication Required";
        break;

    default:
        p = "Unknown";
        debugs(57, 3, "Unknown HTTP status code: " << status);
        break;
    }

    return p;
}
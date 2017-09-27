    }

    /* authz_core will log the require line and the result at DEBUG */
    return AUTHZ_DENIED;
}

static authz_status local_check_authorization(request_rec *r,
                                              const char *require_line,
                                              const void *parsed_require_line)
{
     if (   apr_sockaddr_equal(r->connection->local_addr,
                               r->useragent_addr)

static int is_idempotent(request_rec *r)
{
    /*
     * RFC2616 (9.1.2): GET, HEAD, PUT, DELETE, OPTIONS, TRACE are considered
     * idempotent. Hint: HEAD requests use M_GET as method number as well.
     */
    switch (r->method_number) {
        case M_GET:
        case M_DELETE:
        case M_PUT:
        case M_OPTIONS:
        case M_TRACE:
            /*
             * If the request has arguments it might have side-effects and thus
             * it might be undesirable to resend it to a backend again
             * automatically.
             */
            if (r->args) {
                return METHOD_IDEMPOTENT_WITH_ARGS;
            }
            return METHOD_IDEMPOTENT;
        /* Everything else is not considered idempotent. */
        default:
            return METHOD_NON_IDEMPOTENT;
    }
}
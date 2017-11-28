bool
FwdState::checkRetriable()
{
    /* RFC2616 9.1 Safe and Idempotent Methods */
    switch (request->method.id()) {
        /* 9.1.1 Safe Methods */

    case METHOD_GET:

    case METHOD_HEAD:
        /* 9.1.2 Idempotent Methods */

    case METHOD_PUT:

    case METHOD_DELETE:

    case METHOD_OPTIONS:

    case METHOD_TRACE:
        break;

    default:
        return false;
    }

    return true;
}
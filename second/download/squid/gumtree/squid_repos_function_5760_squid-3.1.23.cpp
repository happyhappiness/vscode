static void
rfc1035SetErrno(int n)
{
    switch (rfc1035_errno = n) {
    case 0:
        rfc1035_error_message = "No error condition";
        break;
    case 1:
        rfc1035_error_message = "Format Error: The name server was "
                                "unable to interpret the query.";
        break;
    case 2:
        rfc1035_error_message = "Server Failure: The name server was "
                                "unable to process this query.";
        break;
    case 3:
        rfc1035_error_message = "Name Error: The domain name does "
                                "not exist.";
        break;
    case 4:
        rfc1035_error_message = "Not Implemented: The name server does "
                                "not support the requested kind of query.";
        break;
    case 5:
        rfc1035_error_message = "Refused: The name server refuses to "
                                "perform the specified operation.";
        break;
    case rfc1035_unpack_error:
        rfc1035_error_message = "The DNS reply message is corrupt or could "
                                "not be safely parsed.";
        break;
    default:
        rfc1035_error_message = "Unknown Error";
        break;
    }
}
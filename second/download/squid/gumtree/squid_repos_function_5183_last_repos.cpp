const char *
rfc1035ErrorMessage(int n)
{
    if (n < 0)
        n = -n;
    switch (n) {
    case 0:
        return "No error condition";
        break;
    case 1:
        return "Format Error: The name server was "
               "unable to interpret the query.";
        break;
    case 2:
        return "Server Failure: The name server was "
               "unable to process this query.";
        break;
    case 3:
        return "Name Error: The domain name does "
               "not exist.";
        break;
    case 4:
        return "Not Implemented: The name server does "
               "not support the requested kind of query.";
        break;
    case 5:
        return "Refused: The name server refuses to "
               "perform the specified operation.";
        break;
    case rfc1035_unpack_error:
        return "The DNS reply message is corrupt or could "
               "not be safely parsed.";
        break;
    default:
        return "Unknown Error";
        break;
    }
}
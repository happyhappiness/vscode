static const char* format_authz_result(authz_status result)
{
    return ((result == AUTHZ_DENIED)
            ? "denied"
            : ((result == AUTHZ_GRANTED)
               ? "granted"
               : "neutral"));
}
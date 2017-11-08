static const char* format_authz_result(authz_status result)
{
    return ((result == AUTHZ_DENIED)
            ? "denied"
            : ((result == AUTHZ_GRANTED)
               ? "granted"
               : ((result == AUTHZ_DENIED_NO_USER)
                  ? "denied (no authenticated user)"
                  : "neutral")));
}
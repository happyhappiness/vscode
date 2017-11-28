ESIVariableUserAgent::esiUserOs_t
ESIVariableUserAgent::identifyOs(char const *s) const
{
    if (!s)
        return ESI_OS_OTHER;

    if (strstr (s, "Windows"))
        return ESI_OS_WIN;
    else if (strstr (s, "Mac"))
        return ESI_OS_MAC;
    else if (strstr (s, "nix") || strstr (s, "BSD"))
        return ESI_OS_UNIX;
    else
        return ESI_OS_OTHER;
}
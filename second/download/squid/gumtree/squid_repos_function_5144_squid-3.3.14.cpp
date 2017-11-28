wordlist *
ACLMaxUserIP::dump() const
{
    if (!maximum)
        return NULL;

    wordlist *W = NULL;

    if (flags.strict)
        wordlistAdd(&W, "-s");

    char buf[128];

    snprintf(buf, sizeof(buf), "%lu", (unsigned long int) maximum);

    wordlistAdd(&W, buf);

    return W;
}
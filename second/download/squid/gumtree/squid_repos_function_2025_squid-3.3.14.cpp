char const *
URLScheme::const_str() const
{
    if (theScheme_ == AnyP::PROTO_UNKNOWN)
        return "(unknown)";

    static char out[BUFSIZ];
    int p = 0;

    if (theScheme_ > AnyP::PROTO_NONE && theScheme_ < AnyP::PROTO_MAX) {
        const char *in = AnyP::ProtocolType_str[theScheme_];
        for (; p < (BUFSIZ-1) && in[p] != '\0'; ++p)
            out[p] = xtolower(in[p]);
    }
    out[p] = '\0';
    return out;
}
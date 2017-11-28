void
ACLProtocolData::parse()
{
    while (char *t = ConfigParser::strtokFile()) {
        int p = AnyP::PROTO_NONE;
        for (; p < AnyP::PROTO_UNKNOWN; ++p) {
            if (strcasecmp(t, AnyP::ProtocolType_str[p]) == 0) {
                values.push_back(static_cast<AnyP::ProtocolType>(p));
                break;
            }
        }
        if (p == AnyP::PROTO_UNKNOWN) {
            debugs(28, DBG_IMPORTANT, "WARNING: Ignoring unknown protocol '" << t << "' in the ACL named '" << AclMatchedName << "'");
            // XXX: store the text pattern of this protocol name for live comparisons
        }
    }
}
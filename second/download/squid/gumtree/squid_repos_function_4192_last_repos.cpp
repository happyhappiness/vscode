SBufList
ACLAtStepData::dump() const
{
    SBufList sl;
    for (std::list<Ssl::BumpStep>::const_iterator it = values.begin(); it != values.end(); ++it) {
        sl.push_back(SBuf(*it == Ssl::bumpStep1 ? "SslBump1" :
                          *it == Ssl::bumpStep2 ? "SslBump2" :
                          *it == Ssl::bumpStep3 ? "SslBump3" : "???"));
    }
    return sl;
}
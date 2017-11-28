bool
ACLAtStepData::match(Ssl::BumpStep  toFind)
{
    for (std::list<Ssl::BumpStep>::const_iterator it = values.begin(); it != values.end(); ++it) {
        if (*it == toFind)
            return true;
    }
    return false;
}
bool
ACLProtocolData::match(AnyP::ProtocolType toFind)
{
    for (auto itr = values.begin(); itr != values.end(); ++itr) {
        if (*itr == toFind) {
            // tune the list for LRU ordering
            values.erase(itr);
            values.push_front(toFind);
            return true;
        }
    }
    return false;
}
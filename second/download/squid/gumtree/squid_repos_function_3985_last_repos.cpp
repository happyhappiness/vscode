bool
ACLMethodData::match(HttpRequestMethod toFind)
{
    for (auto i = values.begin(); i != values.end(); ++i) {
        if (*i == toFind) {
            // tune the list for LRU ordering
            values.erase(i);
            values.push_front(toFind);
            return true;
        }
    }
    return false;
}
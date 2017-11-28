bool Adaptation::Icap::Options::TransferList::matches(const SBuf &urlPath) const
{
    const SBuf::size_type urlLen = urlPath.length();
    for (wordlist *e = extensions; e; e = e->next) {
        // optimize: store extension lengths
        const size_t eLen = strlen(e->key);

        // assume URL contains at least '/' before the extension
        if (eLen < urlLen) {
            const size_t eOff = urlLen - eLen;
            // RFC 3507 examples imply that extensions come without leading '.'
            if (urlPath[eOff-1] == '.' && urlPath.substr(eOff).cmp(e->key, eLen) == 0) {
                debugs(93,7, "url " << urlPath << " matches " << name << " extension " << e->key);
                return true;
            }
        }
    }
    debugs(93,8, "url " << urlPath << " matches no " << name << " extensions");
    return false;
}
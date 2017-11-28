bool Adaptation::Icap::Options::TransferList::matches(const String &urlPath) const
{
    const int urlLen = urlPath.size();
    for (wordlist *e = extensions; e; e = e->next) {
        // optimize: store extension lengths
        const int eLen = strlen(e->key);

        // assume URL contains at least '/' before the extension
        if (eLen < urlLen) {
            const int eOff = urlLen - eLen;
            // RFC 3507 examples imply that extensions come without leading '.'
            if (urlPath[eOff-1] == '.' &&
                    strcmp(urlPath.termedBuf() + eOff, e->key) == 0) {
                debugs(93,7, HERE << "url " << urlPath << " matches " <<
                       name << " extension " << e->key);
                return true;
            }
        }
    }
    debugs(93,8, HERE << "url " << urlPath << " matches no " << name << " extensions");
    return false;
}
bool
StoreEntry::modifiedSince(const time_t ims, const int imslen) const
{
    int object_length;
    const time_t mod_time = lastModified();

    debugs(88, 3, "modifiedSince: '" << url() << "'");

    debugs(88, 3, "modifiedSince: mod_time = " << mod_time);

    if (mod_time < 0)
        return true;

    /* Find size of the object */
    object_length = getReply()->content_length;

    if (object_length < 0)
        object_length = contentLen();

    if (mod_time > ims) {
        debugs(88, 3, "--> YES: entry newer than client");
        return true;
    } else if (mod_time < ims) {
        debugs(88, 3, "-->  NO: entry older than client");
        return false;
    } else if (imslen < 0) {
        debugs(88, 3, "-->  NO: same LMT, no client length");
        return false;
    } else if (imslen == object_length) {
        debugs(88, 3, "-->  NO: same LMT, same length");
        return false;
    } else {
        debugs(88, 3, "--> YES: same LMT, different length");
        return true;
    }
}
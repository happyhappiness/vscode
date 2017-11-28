bool
Acl::OptionExtractor::extractOne()
{
    if (!prefix_.isEmpty()) {
        extractShort(); // continue with the previously extracted flags
        return true;
    }

    if (!advance())
        return false; // end of options (and, possibly, the whole "acl" directive)

    if (prefix_.length() < 2)
        throw TexcHere(ToSBuf("truncated(?) ACL flag: ", prefix_)); // single - or +

    if (prefix_[0] == '-' && prefix_[1] == '-') {
        if (prefix_.length() == 2)
            return false; // skipped "--", an explicit end-of-options marker
        extractWhole();
        return true;
    }

    if (prefix_.length() == 2) { // common trivial case: -x or +y
        extractWhole();
        return true;
    }

    // -xyz or +xyz
    letterPos_ = 1;
    extractShort();
    return true;
}
bool
ACLHierCodeData::empty() const
{
    for (hier_code iter = HIER_NONE; iter <= HIER_MAX; ++iter) {
        if (values[iter]) return false; // not empty.
    }
    return true;
}
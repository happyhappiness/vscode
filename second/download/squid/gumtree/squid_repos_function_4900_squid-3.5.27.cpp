SBufList
ACLRegexData::dump() const
{
    SBufList sl;
    RegexList *temp = data;
    int flags = REG_EXTENDED | REG_NOSUB;

    while (temp != NULL) {
        if (temp->flags != flags) {
            if ((temp->flags&REG_ICASE) != 0) {
                sl.push_back(SBuf("-i"));
            } else {
                sl.push_back(SBuf("+i"));
            }
            flags = temp->flags;
        }

        sl.push_back(SBuf(temp->pattern));
        temp = temp->next;
    }

    return sl;
}
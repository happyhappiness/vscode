wordlist *
ACLRegexData::dump()
{
    wordlist *W = NULL;
    RegexList *temp = data;
    int flags = REG_EXTENDED | REG_NOSUB;

    while (temp != NULL) {
        if (temp->flags != flags) {
            if ((temp->flags&REG_ICASE) != 0) {
                wordlistAdd(&W, "-i");
            } else {
                wordlistAdd(&W, "+i");
            }
            flags = temp->flags;
        }

        wordlistAdd(&W, temp->pattern);
        temp = temp->next;
    }

    return W;
}
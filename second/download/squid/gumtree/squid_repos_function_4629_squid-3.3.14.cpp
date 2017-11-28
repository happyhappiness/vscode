bool
ACLRegexData::match(char const *word)
{
    if (word == NULL)
        return 0;

    debugs(28, 3, "aclRegexData::match: checking '" << word << "'");

    RegexList *first, *prev;

    first = data;

    prev = NULL;

    RegexList *current = first;

    while (current) {
        debugs(28, 3, "aclRegexData::match: looking for '" << current->pattern << "'");

        if (regexec(&current->regex, word, 0, 0, 0) == 0) {
            if (prev != NULL) {
                /* shift the element just found to the second position
                 * in the list */
                prev->next = current->next;
                current->next = first->next;
                first->next = current;
            }

            debugs(28, 2, "aclRegexData::match: match '" << current->pattern << "' found in '" << word << "'");
            return 1;
        }

        prev = current;
        current = current->next;
    }

    return 0;
}
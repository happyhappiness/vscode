bool

TrieNode::add
(char const *aString, size_t theLength, void *privatedata, TrieCharTransform *transform)
{
    /* We trust that privatedata and existant keys have already been checked */

    if (theLength) {
        int index = transform ? (*transform) (*aString): *aString;

        if (!internal[index])
            internal[index] = new TrieNode;

        return internal[index]->add
               (aString + 1, theLength - 1, privatedata, transform);
    } else {
        /* terminal node */

        if (_privateData)
            return false;

        _privateData = privatedata;

        return true;
    }
}
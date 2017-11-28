bool
Trie::add(char const *aString, size_t theLength, void *privatedata)
{
    if (!privatedata)
        return false;

    if (head) {
        if (find(aString, theLength))
            return false;

        return head->add(aString, theLength, privatedata, transform);
    }

    head = new TrieNode;

    return head->add(aString, theLength, privatedata, transform);
}
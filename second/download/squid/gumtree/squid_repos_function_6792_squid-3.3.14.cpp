int TrieAdd(void *aTrie, char const *aString, size_t theLength, void *privatedata)
{

    return ((Trie *)aTrie)->add(aString, theLength, privatedata);
}
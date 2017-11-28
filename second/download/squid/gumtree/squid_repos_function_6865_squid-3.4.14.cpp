void *TrieFind(void *aTrie, char const *aString, size_t theLength)
{
    return ((Trie *)aTrie)->find(aString, theLength);
}
wordlist *
ACLRandom::dump() const
{
    wordlist *w = NULL;
    wordlistAdd(&w, pattern);
    return w;
}
const cache_key *
storeKeyPrivate()
{
    // only the count field is required
    // others just simplify searching for keys in a multi-process cache.log
    static struct {
        uint64_t count;
        pid_t pid;
        int32_t kid;
    } key = { 0, getpid(), KidIdentifier };
    assert(sizeof(key) == SQUID_MD5_DIGEST_LENGTH);
    ++key.count;
    return reinterpret_cast<cache_key*>(&key);
}
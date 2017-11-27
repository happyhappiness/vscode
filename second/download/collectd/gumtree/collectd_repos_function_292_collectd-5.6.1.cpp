static uint32_t kafka_hash(const char *keydata, size_t keylen)
{
    uint32_t hash = 5381;
    for (; keylen > 0; keylen--)
        hash = ((hash << 5) + hash) + keydata[keylen - 1];
    return hash;
}
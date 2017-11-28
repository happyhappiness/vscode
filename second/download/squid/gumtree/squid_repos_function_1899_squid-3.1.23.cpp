bool
StoreSearchHashIndex::isDone() const
{
    return bucket >= store_hash_buckets || _done;
}
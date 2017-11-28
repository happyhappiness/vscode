void Ssl::LocalContextStorage::deleteAt(LocalContextStorage::MapIterator i)
{
    if (i != storage.end()) {

        delete *(i->second);
        lru_queue.erase(i->second);
        storage.erase(i);
        memory_used -= SSL_CTX_SIZE;
    }
}
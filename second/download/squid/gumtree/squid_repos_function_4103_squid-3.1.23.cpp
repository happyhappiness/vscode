SSL_CTX * Ssl::LocalContextStorage::find(char const * host_name)
{
    MapIterator i = storage.find(host_name);
    if (i == storage.end()) {
        return NULL;
    }
    lru_queue.push_front(*(i->second));
    lru_queue.erase(i->second);
    i->second = lru_queue.begin();
    return (*lru_queue.begin())->ssl_ctx;
}
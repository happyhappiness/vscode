SSL_CTX * Ssl::LocalContextStorage::add(const char * host_name, SSL_CTX * ssl_ctx)
{
    if (max_memory < SSL_CTX_SIZE) {
        return NULL;
    }
    remove(host_name);
    while (SSL_CTX_SIZE + memory_used > max_memory) {
        purgeOne();
    }
    lru_queue.push_front(new Item(ssl_ctx, host_name));
    storage.insert(MapPair(host_name, lru_queue.begin()));
    memory_used += SSL_CTX_SIZE;
    return ssl_ctx;
}
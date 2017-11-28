void Ssl::LocalContextStorage::purgeOne()
{
    QueueIterator i = lru_queue.end();
    --i;
    if (i != lru_queue.end()) {
        remove((*i)->host_name.c_str());
    }
}
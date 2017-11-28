void Ssl::LocalContextStorage::remove(char const * host_name)
{
    deleteAt(storage.find(host_name));
}
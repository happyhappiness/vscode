void Ssl::GlobalContextStorage::addLocalStorage(IpAddress const & address, size_t size_of_store)
{
    assert(reconfiguring);
    configureStorage.insert(std::pair<IpAddress, size_t>(address, size_of_store));
}
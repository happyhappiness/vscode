void Ssl::GlobalContextStorage::addLocalStorage(Ip::Address const & address, size_t size_of_store)
{
    assert(reconfiguring);
    configureStorage.insert(std::pair<Ip::Address, size_t>(address, size_of_store));
}
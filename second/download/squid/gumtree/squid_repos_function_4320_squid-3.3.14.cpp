Ssl::LocalContextStorage & Ssl::GlobalContextStorage::getLocalStorage(Ip::Address const & address)
{
    reconfigureFinish();
    std::map<Ip::Address, LocalContextStorage *>::iterator i = storage.find(address);
    assert (i != storage.end());
    return *(i->second);
}
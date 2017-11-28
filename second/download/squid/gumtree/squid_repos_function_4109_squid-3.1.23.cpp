Ssl::LocalContextStorage & Ssl::GlobalContextStorage::getLocalStorage(IpAddress const & address)
{
    reconfigureFinish();
    std::map<IpAddress, LocalContextStorage *>::iterator i = storage.find(address);
    assert (i != storage.end());
    return *(i->second);
}
Ssl::LocalContextStorage *Ssl::GlobalContextStorage::getLocalStorage(Ip::Address const & address)
{
    reconfigureFinish();
    std::map<Ip::Address, LocalContextStorage *>::iterator i = storage.find(address);

    if (i == storage.end())
        return NULL;
    else
        return i->second;
}
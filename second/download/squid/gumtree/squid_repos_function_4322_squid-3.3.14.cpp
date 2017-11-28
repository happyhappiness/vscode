void Ssl::GlobalContextStorage::reconfigureFinish()
{
    if (reconfiguring) {
        reconfiguring = false;

        // remove or change old local storages.
        for (std::map<Ip::Address, LocalContextStorage *>::iterator i = storage.begin(); i != storage.end(); ++i) {
            std::map<Ip::Address, size_t>::iterator conf_i = configureStorage.find(i->first);
            if (conf_i == configureStorage.end()) {
                storage.erase(i);
            } else {
                i->second->SetSize(conf_i->second);
            }
        }

        // add new local storages.
        for (std::map<Ip::Address, size_t>::iterator conf_i = configureStorage.begin(); conf_i != configureStorage.end(); ++conf_i ) {
            if (storage.find(conf_i->first) == storage.end()) {
                storage.insert(std::pair<Ip::Address, LocalContextStorage *>(conf_i->first, new LocalContextStorage(conf_i->second)));
            }
        }
    }
}
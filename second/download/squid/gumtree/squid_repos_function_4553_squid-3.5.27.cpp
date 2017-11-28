void Ssl::GlobalContextStorage::reconfigureFinish()
{
    if (reconfiguring) {
        reconfiguring = false;

        // remove or change old local storages.
        for (std::map<Ip::Address, LocalContextStorage *>::iterator i = storage.begin(); i != storage.end();) {
            std::map<Ip::Address, size_t>::iterator conf_i = configureStorage.find(i->first);
            if (conf_i == configureStorage.end() || conf_i->second <= 0) {
                delete i->second;
                storage.erase(i++);
            } else {
                i->second->setMemLimit(conf_i->second);
                ++i;
            }
        }

        // add new local storages.
        for (std::map<Ip::Address, size_t>::iterator conf_i = configureStorage.begin(); conf_i != configureStorage.end(); ++conf_i ) {
            if (storage.find(conf_i->first) == storage.end() && conf_i->second > 0) {
                storage.insert(std::pair<Ip::Address, LocalContextStorage *>(conf_i->first, new LocalContextStorage(-1, conf_i->second)));
            }
        }
    }
}
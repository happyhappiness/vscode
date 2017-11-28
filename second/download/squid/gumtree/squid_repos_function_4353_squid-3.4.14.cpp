void Ssl::CertificateStorageAction::dump (StoreEntry *sentry)
{
    StoreEntryStream stream(sentry);
    const char delimiter = '\t';
    const char endString = '\n';
    // Page title.
    stream << "Cached ssl certificates statistic.\n";
    // Title of statistic table.
    stream << "Port" << delimiter << "Max mem(KB)" << delimiter << "Cert number" << delimiter << "KB/cert" << delimiter << "Mem used(KB)" << delimiter << "Mem free(KB)" << endString;

    // Add info for each port.
    for (std::map<Ip::Address, LocalContextStorage *>::iterator i = TheGlobalContextStorage.storage.begin(); i != TheGlobalContextStorage.storage.end(); ++i) {
        stream << i->first << delimiter;
        LocalContextStorage & ssl_store_policy(*(i->second));
        stream << ssl_store_policy.memLimit() / 1024 << delimiter;
        stream << ssl_store_policy.entries() << delimiter;
        stream << SSL_CTX_SIZE / 1024 << delimiter;
        stream << ssl_store_policy.size() / 1024 << delimiter;
        stream << ssl_store_policy.freeMem() / 1024 << endString;
    }
    stream << endString;
    stream.flush();
}
void
Adaptation::Config::dumpService(StoreEntry *entry, const char *name) const
{
    typedef Services::iterator SCI;
    for (SCI i = AllServices().begin(); i != AllServices().end(); ++i) {
        const ServiceConfig &cfg = (*i)->cfg();
        bool isEcap = cfg.protocol.caseCmp("ecap") == 0;
        bool isIcap = !isEcap;
        const char *optConnectionEncryption = "";
        // Print connections_encrypted option if no default value is used
        if (cfg.secure.encryptTransport && !cfg.connectionEncryption)
            optConnectionEncryption = " connection-encryption=off";
        else if (isEcap && !cfg.connectionEncryption)
            optConnectionEncryption = " connection-encryption=off";
        else if (isIcap && !cfg.secure.encryptTransport && cfg.connectionEncryption)
            optConnectionEncryption = " connection-encryption=on";

        storeAppendPrintf(entry, "%s " SQUIDSTRINGPH " %s_%s %d " SQUIDSTRINGPH "%s\n",
                          name,
                          SQUIDSTRINGPRINT(cfg.key),
                          cfg.methodStr(), cfg.vectPointStr(), cfg.bypass,
                          SQUIDSTRINGPRINT(cfg.uri),

                          optConnectionEncryption);
    }
}
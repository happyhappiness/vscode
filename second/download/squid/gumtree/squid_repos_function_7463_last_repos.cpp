void
Security::PeerOptions::dumpCfg(Packable *p, const char *pfx) const
{
    if (!encryptTransport) {
        p->appendf(" %sdisable", pfx);
        return; // no other settings are relevant
    }

    for (auto &i : certs) {
        if (!i.certFile.isEmpty())
            p->appendf(" %scert=" SQUIDSBUFPH, pfx, SQUIDSBUFPRINT(i.certFile));

        if (!i.privateKeyFile.isEmpty() && i.privateKeyFile != i.certFile)
            p->appendf(" %skey=" SQUIDSBUFPH, pfx, SQUIDSBUFPRINT(i.privateKeyFile));
    }

    if (!sslOptions.isEmpty())
        p->appendf(" %soptions=" SQUIDSBUFPH, pfx, SQUIDSBUFPRINT(sslOptions));

    if (!sslCipher.isEmpty())
        p->appendf(" %scipher=" SQUIDSBUFPH, pfx, SQUIDSBUFPRINT(sslCipher));

    for (auto i : caFiles) {
        p->appendf(" %scafile=" SQUIDSBUFPH, pfx, SQUIDSBUFPRINT(i));
    }

    if (!caDir.isEmpty())
        p->appendf(" %scapath=" SQUIDSBUFPH, pfx, SQUIDSBUFPRINT(caDir));

    if (!crlFile.isEmpty())
        p->appendf(" %scrlfile=" SQUIDSBUFPH, pfx, SQUIDSBUFPRINT(crlFile));

    if (!sslFlags.isEmpty())
        p->appendf(" %sflags=" SQUIDSBUFPH, pfx, SQUIDSBUFPRINT(sslFlags));

    if (flags.tlsDefaultCa.configured()) {
        // default ON for peers / upstream servers
        // default OFF for listening ports
        if (flags.tlsDefaultCa)
            p->appendf(" %sdefault-ca", pfx);
        else
            p->appendf(" %sdefault-ca=off", pfx);
    }

    if (!flags.tlsNpn)
        p->appendf(" %sno-npn", pfx);
}
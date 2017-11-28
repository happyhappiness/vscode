void
Ssl::unloadSquidUntrusted()
{
    if (SquidUntrustedCerts.size()) {
        for (Ssl::CertsIndexedList::iterator it = SquidUntrustedCerts.begin(); it != SquidUntrustedCerts.end(); ++it) {
            X509_free(it->second);
        }
        SquidUntrustedCerts.clear();
    }
}
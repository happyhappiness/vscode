    }
}

bool
Ssl::ServerBio::resumingSession()
{
    if (!serverFeatures.initialized_)
        serverFeatures.get(rbuf, false);

    if (!clientFeatures.sessionId.isEmpty() && !serverFeatures.sessionId.isEmpty())
        return clientFeatures.sessionId == serverFeatures.sessionId;

    // is this a session resuming attempt using TLS tickets?
    if (clientFeatures.hasTlsTicket && serverFeatures.hasCcsOrNst)
        return true;

    return false;
}

/// initializes BIO table after allocation
static int
squid_bio_create(BIO *bi)
{
    bi->init = 0; // set when we store Bio object and socket fd (BIO_C_SET_FD)
    bi->num = 0;
    bi->ptr = NULL;
    bi->flags = 0;
    return 1;
}

/// cleans BIO table before deallocation
static int
squid_bio_destroy(BIO *table)
{
    delete static_cast<Ssl::Bio*>(table->ptr);
    table->ptr = NULL;
    return 1;
}

/// wrapper for Bio::write()
static int
squid_bio_write(BIO *table, const char *buf, int size)
{
    Ssl::Bio *bio = static_cast<Ssl::Bio*>(table->ptr);
    assert(bio);
    return bio->write(buf, size, table);
}

/// wrapper for Bio::read()
static int
squid_bio_read(BIO *table, char *buf, int size)
{
    Ssl::Bio *bio = static_cast<Ssl::Bio*>(table->ptr);
    assert(bio);
    return bio->read(buf, size, table);
}

/// implements puts() via write()
static int

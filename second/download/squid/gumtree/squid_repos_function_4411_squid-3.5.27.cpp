static int
squid_bio_write(BIO *table, const char *buf, int size)
{
    Ssl::Bio *bio = static_cast<Ssl::Bio*>(table->ptr);
    assert(bio);
    return bio->write(buf, size, table);
}
static int
squid_bio_destroy(BIO *table)
{
    delete static_cast<Ssl::Bio*>(table->ptr);
    table->ptr = NULL;
    return 1;
}
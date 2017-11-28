void
Ssl::ServerBio::flush(BIO *table)
{
    if (!helloMsg.isEmpty()) {
        int ret = Ssl::Bio::write(helloMsg.rawContent(), helloMsg.length(), table);
        helloMsg.consume(ret);
    }
}
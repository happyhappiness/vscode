int
Ssl::ClientBio::write(const char *buf, int size, BIO *table)
{
    if (abortReason) {
        debugs(83, 3, "BIO on FD " << fd_ << " is aborted");
        BIO_clear_retry_flags(table);
        return -1;
    }

    if (holdWrite_) {
        BIO_set_retry_write(table);
        return 0;
    }

    return Ssl::Bio::write(buf, size, table);
}
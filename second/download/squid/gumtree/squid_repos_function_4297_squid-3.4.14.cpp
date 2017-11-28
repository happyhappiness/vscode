static void
ssl_free_ErrorDetail(void *, void *ptr, CRYPTO_EX_DATA *,
                     int, long, void *)
{
    Ssl::ErrorDetail  *errDetail = static_cast <Ssl::ErrorDetail *>(ptr);
    delete errDetail;
}
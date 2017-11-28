static void
ssl_free_SBuf(void *, void *ptr, CRYPTO_EX_DATA *,
              int, long, void *)
{
    SBuf  *buf = static_cast <SBuf *>(ptr);
    delete buf;
}
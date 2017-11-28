static void
ssl_free_int(void *, void *ptr, CRYPTO_EX_DATA *,
             int, long, void *)
{
    uint32_t *counter = static_cast <uint32_t *>(ptr);
    delete counter;
}
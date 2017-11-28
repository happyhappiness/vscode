const char *
Security::NegotiationHistory::cipherName() const
{
#if USE_OPENSSL
    if (!cipher)
        return nullptr;

    return SSL_CIPHER_get_name(cipher);
#else
    return nullptr;
#endif
}
void
Ident::Init(void)
{
    if (ident_hash) {
        debugs(30, DBG_CRITICAL, "WARNING: Ident already initialized.");
        return;
    }

    ident_hash = hash_create((HASHCMP *) strcmp,
                             hashPrime(Squid_MaxFD / 8),
                             hash4);
}
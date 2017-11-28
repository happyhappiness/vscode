void
StoreEntry::clearPublicKeyScope()
{
    if (!key || EBIT_TEST(flags, KEY_PRIVATE))
        return; // probably the old public key was deleted or made private

    // TODO: adjustVary() when collapsed revalidation supports that

    const cache_key *newKey = calcPublicKey(ksDefault);
    if (!storeKeyHashCmp(key, newKey))
        return; // probably another collapsed revalidation beat us to this change

    forcePublicKey(newKey);
}
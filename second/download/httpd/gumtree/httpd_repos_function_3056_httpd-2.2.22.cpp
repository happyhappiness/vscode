static apr_status_t crypto_passphrase(apr_crypto_key_t **k, apr_size_t *ivSize,
        const char *pass, apr_size_t passLen, const unsigned char * salt,
        apr_size_t saltLen, const apr_crypto_block_key_type_e type,
        const apr_crypto_block_key_mode_e mode, const int doPad,
        const int iterations, const apr_crypto_t *f, apr_pool_t *p)
{
    apr_status_t rv = APR_SUCCESS;
    PK11SlotInfo * slot;
    SECItem passItem;
    SECItem saltItem;
    SECAlgorithmID *algid;
    void *wincx = NULL; /* what is wincx? */
    apr_crypto_key_t *key = *k;

    if (!key) {
        *k = key = apr_array_push(f->keys);
    }
    if (!key) {
        return APR_ENOMEM;
    }

    key->f = f;
    key->provider = f->provider;

    /* decide on what cipher mechanism we will be using */
    switch (type) {

    case (APR_KEY_3DES_192):
        if (APR_MODE_CBC == mode) {
            key->cipherOid = SEC_OID_DES_EDE3_CBC;
        }
        else if (APR_MODE_ECB == mode) {
            return APR_ENOCIPHER;
            /* No OID for CKM_DES3_ECB; */
        }
        break;
    case (APR_KEY_AES_128):
        if (APR_MODE_CBC == mode) {
            key->cipherOid = SEC_OID_AES_128_CBC;
        }
        else {
            key->cipherOid = SEC_OID_AES_128_ECB;
        }
        break;
    case (APR_KEY_AES_192):
        if (APR_MODE_CBC == mode) {
            key->cipherOid = SEC_OID_AES_192_CBC;
        }
        else {
            key->cipherOid = SEC_OID_AES_192_ECB;
        }
        break;
    case (APR_KEY_AES_256):
        if (APR_MODE_CBC == mode) {
            key->cipherOid = SEC_OID_AES_256_CBC;
        }
        else {
            key->cipherOid = SEC_OID_AES_256_ECB;
        }
        break;
    default:
        /* unknown key type, give up */
        return APR_EKEYTYPE;
    }

    /* AES_128_CBC --> CKM_AES_CBC --> CKM_AES_CBC_PAD */
    key->cipherMech = PK11_AlgtagToMechanism(key->cipherOid);
    if (key->cipherMech == CKM_INVALID_MECHANISM) {
        return APR_ENOCIPHER;
    }
    if (doPad) {
        CK_MECHANISM_TYPE paddedMech;
        paddedMech = PK11_GetPadMechanism(key->cipherMech);
        if (CKM_INVALID_MECHANISM == paddedMech || key->cipherMech
                == paddedMech) {
            return APR_EPADDING;
        }
        key->cipherMech = paddedMech;
    }

    /* Turn the raw passphrase and salt into SECItems */
    passItem.data = (unsigned char*) pass;
    passItem.len = passLen;
    saltItem.data = (unsigned char*) salt;
    saltItem.len = saltLen;

    /* generate the key */
    /* pbeAlg and cipherAlg are the same. NSS decides the keylength. */
    algid = PK11_CreatePBEV2AlgorithmID(key->cipherOid, key->cipherOid,
            SEC_OID_HMAC_SHA1, 0, iterations, &saltItem);
    if (algid) {
        slot = PK11_GetBestSlot(key->cipherMech, wincx);
        if (slot) {
            key->symKey = PK11_PBEKeyGen(slot, algid, &passItem, PR_FALSE,
                    wincx);
            PK11_FreeSlot(slot);
        }
        SECOID_DestroyAlgorithmID(algid, PR_TRUE);
    }

    /* sanity check? */
    if (!key->symKey) {
        PRErrorCode perr = PORT_GetError();
        if (perr) {
            f->result->rc = perr;
            f->result->msg = PR_ErrorToName(perr);
            rv = APR_ENOKEY;
        }
    }

    key->ivSize = PK11_GetIVLength(key->cipherMech);
    if (ivSize) {
        *ivSize = key->ivSize;
    }

    return rv;
}
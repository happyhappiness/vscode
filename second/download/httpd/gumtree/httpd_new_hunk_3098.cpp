#include "mod_session.h"
#include "apu_version.h"
#include "apr_base64.h"                /* for apr_base64_decode et al */
#include "apr_lib.h"
#include "apr_strings.h"
#include "http_log.h"
#include "http_core.h"

#if APU_MAJOR_VERSION == 1 && APU_MINOR_VERSION < 4

#error session_crypto_module requires APU v1.4.0 or later

#elif APU_HAVE_CRYPTO == 0

#error Crypto support must be enabled in APR

#else

#include "apr_crypto.h"                /* for apr_*_crypt et al */

#define CRYPTO_KEY "session_crypto_context"

module AP_MODULE_DECLARE_DATA session_crypto_module;

/**
 * Structure to carry the per-dir session config.
 */
typedef struct {
    apr_array_header_t *passphrases;
    int passphrases_set;
    const char *cipher;
    int cipher_set;
} session_crypto_dir_conf;

/**
 * Structure to carry the server wide session config.
 */
typedef struct {
    const char *library;
    const char *params;
    int library_set;
} session_crypto_conf;

/**
 * Initialise the encryption as per the current config.
 *
 * Returns APR_SUCCESS if successful.
 */
static apr_status_t crypt_init(request_rec *r,
        const apr_crypto_t *f, apr_crypto_block_key_type_e **cipher,
        session_crypto_dir_conf * dconf)
{
    apr_status_t res;
    apr_hash_t *ciphers;

    res = apr_crypto_get_block_key_types(&ciphers, f);
    if (APR_SUCCESS != res) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, res, r, APLOGNO(01823)
                "no ciphers returned by APR. "
                "session encryption not possible");
        return res;
    }

    *cipher = apr_hash_get(ciphers, dconf->cipher, APR_HASH_KEY_STRING);
    if (!(*cipher)) {
        apr_hash_index_t *hi;
        const void *key;
        apr_ssize_t klen;
        int sum = 0;
        int offset = 0;
        char *options = NULL;

        for (hi = apr_hash_first(r->pool, ciphers); hi; hi = apr_hash_next(hi)) {
            apr_hash_this(hi, NULL, &klen, NULL);
            sum += klen + 2;
        }
        for (hi = apr_hash_first(r->pool, ciphers); hi; hi = apr_hash_next(hi)) {
            apr_hash_this(hi, &key, &klen, NULL);
            if (!options) {
                options = apr_palloc(r->pool, sum + 1);
            }
            else {
                options[offset++] = ',';
                options[offset++] = ' ';
            }
            strncpy(options + offset, key, klen);
            offset += klen;
        }
        options[offset] = 0;

        ap_log_rerror(APLOG_MARK, APLOG_ERR, res, r, APLOGNO(01824)
                "cipher '%s' not recognised by crypto driver. "
                "session encryption not possible, options: %s", dconf->cipher, options);

        return APR_EGENERAL;
    }

    return APR_SUCCESS;
}

/**
 * Encrypt the string given as per the current config.
 *
 * Returns APR_SUCCESS if successful.
 */
static apr_status_t encrypt_string(request_rec * r, const apr_crypto_t *f,
        session_crypto_dir_conf *dconf, const char *in, char **out)
{
    apr_status_t res;
    apr_crypto_key_t *key = NULL;
    apr_size_t ivSize = 0;
    apr_crypto_block_t *block = NULL;
    unsigned char *encrypt = NULL;
    unsigned char *combined = NULL;
    apr_size_t encryptlen, tlen;
    char *base64;
    apr_size_t blockSize = 0;
    const unsigned char *iv = NULL;
    apr_uuid_t salt;
    apr_crypto_block_key_type_e *cipher;
    const char *passphrase;

    /* by default, return an empty string */
    *out = "";

    /* don't attempt to encrypt an empty string, trying to do so causes a segfault */
    if (!in || !*in) {
        return APR_SUCCESS;
    }

    /* use a uuid as a salt value, and prepend it to our result */
    apr_uuid_get(&salt);
    res = crypt_init(r, f, &cipher, dconf);
    if (res != APR_SUCCESS) {
        return res;
    }

    /* encrypt using the first passphrase in the list */
    passphrase = APR_ARRAY_IDX(dconf->passphrases, 0, char *);
    res = apr_crypto_passphrase(&key, &ivSize, passphrase,
            strlen(passphrase),
            (unsigned char *) (&salt), sizeof(apr_uuid_t),
            *cipher, APR_MODE_CBC, 1, 4096, f, r->pool);
    if (APR_STATUS_IS_ENOKEY(res)) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, res, r, APLOGNO(01825)
                "the passphrase '%s' was empty", passphrase);
    }
    if (APR_STATUS_IS_EPADDING(res)) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, res, r, APLOGNO(01826)
                "padding is not supported for cipher");
    }
    if (APR_STATUS_IS_EKEYTYPE(res)) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, res, r, APLOGNO(01827)
                "the key type is not known");
    }
    if (APR_SUCCESS != res) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, res, r, APLOGNO(01828)
                "encryption could not be configured.");
        return res;
    }

    res = apr_crypto_block_encrypt_init(&block, &iv, key, &blockSize, r->pool);
    if (APR_SUCCESS != res) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, res, r, APLOGNO(01829)
                "apr_crypto_block_encrypt_init failed");
        return res;
    }

    /* encrypt the given string */
    res = apr_crypto_block_encrypt(&encrypt, &encryptlen, (unsigned char *)in,
            strlen(in), block);
    if (APR_SUCCESS != res) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, res, r, APLOGNO(01830)
                "apr_crypto_block_encrypt failed");
        return res;
    }
    res = apr_crypto_block_encrypt_finish(encrypt + encryptlen, &tlen, block);
    if (APR_SUCCESS != res) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, res, r, APLOGNO(01831)
                "apr_crypto_block_encrypt_finish failed");
        return res;
    }
    encryptlen += tlen;

    /* prepend the salt and the iv to the result */
    combined = apr_palloc(r->pool, ivSize + encryptlen + sizeof(apr_uuid_t));
    memcpy(combined, &salt, sizeof(apr_uuid_t));
    memcpy(combined + sizeof(apr_uuid_t), iv, ivSize);
    memcpy(combined + sizeof(apr_uuid_t) + ivSize, encrypt, encryptlen);

    /* base64 encode the result */
    base64 = apr_palloc(r->pool, apr_base64_encode_len(ivSize + encryptlen +
                    sizeof(apr_uuid_t) + 1)
            * sizeof(char));
    apr_base64_encode(base64, (const char *) combined,
            ivSize + encryptlen + sizeof(apr_uuid_t));
    *out = base64;

    return res;

}

/**
 * Decrypt the string given as per the current config.
 *
 * Returns APR_SUCCESS if successful.
 */
static apr_status_t decrypt_string(request_rec * r, const apr_crypto_t *f,
        session_crypto_dir_conf *dconf, const char *in, char **out)
{
    apr_status_t res;
    apr_crypto_key_t *key = NULL;
    apr_size_t ivSize = 0;
    apr_crypto_block_t *block = NULL;
    unsigned char *decrypted = NULL;
    apr_size_t decryptedlen, tlen;
    apr_size_t decodedlen;
    char *decoded;
    apr_size_t blockSize = 0;
    apr_crypto_block_key_type_e *cipher;
    int i = 0;

    /* strip base64 from the string */
    decoded = apr_palloc(r->pool, apr_base64_decode_len(in));
    decodedlen = apr_base64_decode(decoded, in);
    decoded[decodedlen] = '\0';

    res = crypt_init(r, f, &cipher, dconf);
    if (res != APR_SUCCESS) {
        return res;
    }

    /* try each passphrase in turn */
    for (; i < dconf->passphrases->nelts; i++) {
        const char *passphrase = APR_ARRAY_IDX(dconf->passphrases, i, char *);
        apr_size_t len = decodedlen;
        char *slider = decoded;

        /* encrypt using the first passphrase in the list */
        res = apr_crypto_passphrase(&key, &ivSize, passphrase,
                strlen(passphrase),
                (unsigned char *)decoded, sizeof(apr_uuid_t),
                *cipher, APR_MODE_CBC, 1, 4096, f, r->pool);
        if (APR_STATUS_IS_ENOKEY(res)) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, res, r, APLOGNO(01832)
                    "the passphrase '%s' was empty", passphrase);
            continue;
        }
        else if (APR_STATUS_IS_EPADDING(res)) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, res, r, APLOGNO(01833)
                    "padding is not supported for cipher");
            continue;
        }
        else if (APR_STATUS_IS_EKEYTYPE(res)) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, res, r, APLOGNO(01834)
                    "the key type is not known");
            continue;
        }
        else if (APR_SUCCESS != res) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, res, r, APLOGNO(01835)
                    "encryption could not be configured.");
            continue;
        }

        /* sanity check - decoded too short? */
        if (decodedlen < (sizeof(apr_uuid_t) + ivSize)) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r, APLOGNO(01836)
                    "too short to decrypt, skipping");
            res = APR_ECRYPT;
            continue;
        }

        /* bypass the salt at the start of the decoded block */
        slider += sizeof(apr_uuid_t);
        len -= sizeof(apr_uuid_t);

        res = apr_crypto_block_decrypt_init(&block, &blockSize, (unsigned char *)slider, key,
                r->pool);
        if (APR_SUCCESS != res) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, res, r, APLOGNO(01837)
                    "apr_crypto_block_decrypt_init failed");
            continue;
        }

        /* bypass the iv at the start of the decoded block */
        slider += ivSize;
        len -= ivSize;

        /* decrypt the given string */
        res = apr_crypto_block_decrypt(&decrypted, &decryptedlen,
                (unsigned char *)slider, len, block);
        if (res) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, res, r, APLOGNO(01838)
                    "apr_crypto_block_decrypt failed");
            continue;
        }
        *out = (char *) decrypted;

        res = apr_crypto_block_decrypt_finish(decrypted + decryptedlen, &tlen, block);
        if (APR_SUCCESS != res) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, res, r, APLOGNO(01839)
                    "apr_crypto_block_decrypt_finish failed");
            continue;
        }
        decryptedlen += tlen;
        decrypted[decryptedlen] = 0;

        break;
    }

    if (APR_SUCCESS != res) {
        ap_log_rerror(APLOG_MARK, APLOG_INFO, res, r, APLOGNO(01840)
                "decryption failed");
    }

    return res;

}

/**
 * Crypto encoding for the session.
 *
 * @param r The request pointer.
 * @param z A pointer to where the session will be written.
 */
static apr_status_t session_crypto_encode(request_rec * r, session_rec * z)
{

    char *encoded = NULL;
    apr_status_t res;
    const apr_crypto_t *f = NULL;
    session_crypto_dir_conf *dconf = ap_get_module_config(r->per_dir_config,
            &session_crypto_module);

    if (dconf->passphrases_set && z->encoded && *z->encoded) {
        apr_pool_userdata_get((void **)&f, CRYPTO_KEY, r->server->process->pconf);
        res = encrypt_string(r, f, dconf, z->encoded, &encoded);
        if (res != OK) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, res, r, APLOGNO(01841)
                    "encrypt session failed");
            return res;
        }
        z->encoded = encoded;
    }


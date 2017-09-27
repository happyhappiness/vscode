#include "mod_session.h"
#include "apu_version.h"
#include "apr_base64.h"                /* for apr_base64_decode et al */
#include "apr_lib.h"
#include "apr_strings.h"
#include "http_log.h"

#if APU_MAJOR_VERSION == 1 && APU_MINOR_VERSION < 4

#error session_crypto_module requires APR v1.4.0 or later

#elif APU_HAVE_CRYPTO == 0

#error Crypto support must be enabled in APR

#else

#if APR_MAJOR_VERSION < 2
#define CRYPTO_VERSION 104
#else
#define CRYPTO_VERSION 200
#endif

#include "apr_crypto.h"                /* for apr_*_crypt et al */

#define LOG_PREFIX "mod_session_crypto: "
#define DRIVER_KEY "session_crypto_driver"
#define INIT_KEY "session_crypto_init"

module AP_MODULE_DECLARE_DATA session_crypto_module;

/**
 * Structure to carry the per-dir session config.
 */
typedef struct {
    const char *passphrase;
    apr_array_header_t *params;
    int passphrase_set;
    apr_crypto_block_key_type_e cipher;
    int cipher_set;
}session_crypto_dir_conf;

/**
 * Structure to carry the server wide session config.
 */
typedef struct {
    const char *library;
    apr_array_header_t *params;
    int library_set;
    int noinit;
    int noinit_set;
}session_crypto_conf;

AP_DECLARE(int) ap_session_crypto_encode(request_rec * r, session_rec * z);
AP_DECLARE(int) ap_session_crypto_decode(request_rec * r, session_rec * z);
AP_DECLARE(int) ap_session_crypto_init(apr_pool_t *p, apr_pool_t *plog,
        apr_pool_t *ptemp, server_rec *s);

/**
 * Initialise the encryption as per the current config.
 *
 * Returns APR_SUCCESS if successful.
 */
static apr_status_t crypt_init(request_rec * r, const apr_crypto_driver_t *driver, apr_crypto_t **f, apr_crypto_key_t **key, apr_uuid_t *salt, apr_size_t *ivSize, session_crypto_dir_conf * dconf)
{
    apr_status_t res;

    if (!driver) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, LOG_PREFIX
                "encryption driver not configured, "
                "no SessionCryptoDriver set");
        return APR_EGENERAL;
    }

    if (!dconf->passphrase_set) {
        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, LOG_PREFIX
                "encryption not configured, "
                "no passphrase set");
        return APR_EGENERAL;
    }

    /* set up */
    res = apr_crypto_make(driver, r->pool, dconf->params, f);
    if (APR_ENOTIMPL == res) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, res, r, LOG_PREFIX
                "generic symmetrical encryption is not supported by this "
                "version of APR. session encryption not possible");
    }

    if (APR_SUCCESS == res) {
#if CRYPTO_VERSION < 200
        res = apr_crypto_passphrase(driver, r->pool, *f, dconf->passphrase,
#else
        res = apr_crypto_passphrase(r->pool, *f, dconf->passphrase,
#endif
                strlen(dconf->passphrase),
                (unsigned char *) salt, salt ? sizeof(apr_uuid_t) : 0, dconf->cipher,
                MODE_CBC, 1, 4096, key, ivSize);
    }

    if (APR_STATUS_IS_ENOKEY(res)) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, res, r, LOG_PREFIX
                "the passphrase '%s' was empty", dconf->passphrase);
    }
    if (APR_STATUS_IS_EPADDING(res)) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, res, r, LOG_PREFIX
                "padding is not supported for cipher");
    }
    if (APR_STATUS_IS_EKEYTYPE(res)) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, res, r, LOG_PREFIX
                "the key type is not known");
    }
    if (APR_SUCCESS != res) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, res, r, LOG_PREFIX
                "encryption could not be configured. Please check the "
                "certificates and/or passphrase as appropriate");
        return APR_EGENERAL;
    }

    return APR_SUCCESS;
}

/**
 * Encrypt the string given as per the current config.
 *
 * Returns APR_SUCCESS if successful.
 */
static apr_status_t encrypt_string(request_rec * r, const apr_crypto_driver_t *driver,
        session_crypto_dir_conf *dconf,
        const char *in, char **out)
{
    apr_status_t res;
    apr_crypto_t *f = NULL;
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

    /* by default, return an empty string */
    *out = "";

    /* don't attempt to encrypt an empty string, trying to do so causes a segfault */
    if (!in || !*in) {
        return APR_SUCCESS;
    }

    /* use a uuid as a salt value, and prepend it to our result */
    apr_uuid_get(&salt);
    res = crypt_init(r, driver, &f, &key, &salt, &ivSize, dconf);
    if (res != APR_SUCCESS) {
        return res;
    }

#if CRYPTO_VERSION < 200
    res = apr_crypto_block_encrypt_init(driver, r->pool, f, key, &iv, &block,
#else
    res = apr_crypto_block_encrypt_init(r->pool, f, key, &iv, &block,
#endif
            &blockSize);
    if (APR_SUCCESS != res) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, res, r, LOG_PREFIX
                "apr_crypto_block_encrypt_init failed");
        return res;
    }

    /* encrypt the given string */
#if CRYPTO_VERSION < 200
    res = apr_crypto_block_encrypt(driver, block, &encrypt,
#else
    res = apr_crypto_block_encrypt(f, block, &encrypt,
#endif
            &encryptlen, (unsigned char *)in, strlen(in));
    if (APR_SUCCESS != res) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, res, r, LOG_PREFIX
                "apr_crypto_block_encrypt failed");
        return res;
    }
#if CRYPTO_VERSION < 200
    res = apr_crypto_block_encrypt_finish(driver, block, encrypt + encryptlen,
#else
    res = apr_crypto_block_encrypt_finish(f, block, encrypt + encryptlen,
#endif
            &tlen);
    if (APR_SUCCESS != res) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, res, r, LOG_PREFIX
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
    base64 = apr_palloc(r->pool, apr_base64_encode_len(ivSize + encryptlen + sizeof(apr_uuid_t) + 1) * sizeof(char));
    apr_base64_encode(base64, (const char *) combined, ivSize + encryptlen + sizeof(apr_uuid_t));
    *out = base64;

    return res;

}

/**
 * Decrypt the string given as per the current config.
 *
 * Returns APR_SUCCESS if successful.
 */
static apr_status_t decrypt_string(request_rec * r, const apr_crypto_driver_t *driver,
        session_crypto_dir_conf *dconf,
        const char *in, char **out)
{
    apr_status_t res;
    apr_crypto_t *f = NULL;
    apr_crypto_key_t *key = NULL;
    apr_size_t ivSize = 0;
    apr_crypto_block_t *block = NULL;
    unsigned char *decrypted = NULL;
    apr_size_t decryptedlen, tlen;
    apr_size_t decodedlen;
    char *decoded;
    apr_size_t blockSize = 0;

    /* strip base64 from the string */
    decoded = apr_palloc(r->pool, apr_base64_decode_len(in));
    decodedlen = apr_base64_decode(decoded, in);
    decoded[decodedlen] = '\0';

    res = crypt_init(r, driver, &f, &key, (apr_uuid_t *)decoded, &ivSize, dconf);
    if (res != APR_SUCCESS) {
        return res;
    }

    /* sanity check - decoded too short? */
    if (decodedlen < (sizeof(apr_uuid_t) + ivSize)) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, APR_SUCCESS, r, LOG_PREFIX
                "too short to decrypt, skipping");
        return APR_ECRYPT;
    }

    /* bypass the salt at the start of the decoded block */
    decoded += sizeof(apr_uuid_t);
    decodedlen -= sizeof(apr_uuid_t);

#if CRYPTO_VERSION < 200
    res = apr_crypto_block_decrypt_init(driver, r->pool, f, key, (unsigned char *)decoded, &block,
#else
    res = apr_crypto_block_decrypt_init(r->pool, f, key, (unsigned char *)decoded, &block,
#endif
            &blockSize);
    if (APR_SUCCESS != res) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, res, r, LOG_PREFIX
                "apr_crypto_block_decrypt_init failed");
        return res;
    }

    /* bypass the iv at the start of the decoded block */
    decoded += ivSize;
    decodedlen -= ivSize;

    /* decrypt the given string */
#if CRYPTO_VERSION < 200
    res = apr_crypto_block_decrypt(driver, block, &decrypted,
#else
    res = apr_crypto_block_decrypt(f, block, &decrypted,
#endif
            &decryptedlen, (unsigned char *)decoded, decodedlen);
    if (res) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, res, r, LOG_PREFIX
                "apr_crypto_block_decrypt failed");
        return res;
    }
    *out = (char *) decrypted;

#if CRYPTO_VERSION < 200
    res = apr_crypto_block_decrypt_finish(driver, block, decrypted + decryptedlen,
#else
    res = apr_crypto_block_decrypt_finish(f, block, decrypted + decryptedlen,
#endif
            &tlen);
    if (APR_SUCCESS != res) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, res, r, LOG_PREFIX
                "apr_crypto_block_decrypt_finish failed");
        return res;
    }
    decryptedlen += tlen;
    decrypted[decryptedlen] = 0;

    return APR_SUCCESS;

}

/**
 * Crypto encoding for the session.
 *
 * @param r The request pointer.
 * @param z A pointer to where the session will be written.
 */
AP_DECLARE(int) ap_session_crypto_encode(request_rec * r, session_rec * z)
{

    char *encoded = NULL;
    apr_status_t res;
    const apr_crypto_driver_t *driver = NULL;
    session_crypto_dir_conf *dconf = ap_get_module_config(r->per_dir_config,
            &session_crypto_module);

    if (dconf->passphrase_set && z->encoded && *z->encoded) {
        apr_pool_userdata_get((void **)&driver, DRIVER_KEY, r->server->process->pconf);
        res = encrypt_string(r, driver, dconf, z->encoded, &encoded);
        if (res != OK) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, res, r, LOG_PREFIX
                    "encrypt session failed");
            return res;
        }
        z->encoded = encoded;
    }


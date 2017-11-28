#include "squid-old.h"
#include "errorpage.h"
#include "ssl/ErrorDetail.h"
#if HAVE_MAP
#include <map>
#endif

struct SslErrorEntry {
    Ssl::ssl_error_t value;
    const char *name;
};

static const char *SslErrorDetailDefaultStr = "SSL handshake error (%err_name)";
//Use std::map to optimize search
typedef std::map<Ssl::ssl_error_t, const SslErrorEntry *> SslErrors;
SslErrors TheSslErrors;

static SslErrorEntry TheSslErrorArray[] = {
    {SQUID_ERR_SSL_HANDSHAKE,
        "SQUID_ERR_SSL_HANDSHAKE"},
    {SQUID_X509_V_ERR_DOMAIN_MISMATCH,
     "SQUID_X509_V_ERR_DOMAIN_MISMATCH"},
    {X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT,
     "X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT"},
    {X509_V_ERR_UNABLE_TO_GET_CRL,
     "X509_V_ERR_UNABLE_TO_GET_CRL"},
    {X509_V_ERR_UNABLE_TO_DECRYPT_CERT_SIGNATURE,
     "X509_V_ERR_UNABLE_TO_DECRYPT_CERT_SIGNATURE"},
    {X509_V_ERR_UNABLE_TO_DECRYPT_CRL_SIGNATURE,
     "X509_V_ERR_UNABLE_TO_DECRYPT_CRL_SIGNATURE"},
    {X509_V_ERR_UNABLE_TO_DECODE_ISSUER_PUBLIC_KEY,
     "X509_V_ERR_UNABLE_TO_DECODE_ISSUER_PUBLIC_KEY"},
    {X509_V_ERR_CERT_SIGNATURE_FAILURE,
     "X509_V_ERR_CERT_SIGNATURE_FAILURE"},
    {X509_V_ERR_CRL_SIGNATURE_FAILURE,
     "X509_V_ERR_CRL_SIGNATURE_FAILURE"},
    {X509_V_ERR_CERT_NOT_YET_VALID,
     "X509_V_ERR_CERT_NOT_YET_VALID"},
    {X509_V_ERR_CERT_HAS_EXPIRED,
     "X509_V_ERR_CERT_HAS_EXPIRED"},
    {X509_V_ERR_CRL_NOT_YET_VALID,
     "X509_V_ERR_CRL_NOT_YET_VALID"},
    {X509_V_ERR_CRL_HAS_EXPIRED,
     "X509_V_ERR_CRL_HAS_EXPIRED"},
    {X509_V_ERR_ERROR_IN_CERT_NOT_BEFORE_FIELD,
     "X509_V_ERR_ERROR_IN_CERT_NOT_BEFORE_FIELD"},
    {X509_V_ERR_ERROR_IN_CERT_NOT_AFTER_FIELD,
     "X509_V_ERR_ERROR_IN_CERT_NOT_AFTER_FIELD"},
    {X509_V_ERR_ERROR_IN_CRL_LAST_UPDATE_FIELD,
     "X509_V_ERR_ERROR_IN_CRL_LAST_UPDATE_FIELD"},
    {X509_V_ERR_ERROR_IN_CRL_NEXT_UPDATE_FIELD,
     "X509_V_ERR_ERROR_IN_CRL_NEXT_UPDATE_FIELD"},
    {X509_V_ERR_OUT_OF_MEM,
     "X509_V_ERR_OUT_OF_MEM"},
    {X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT,
     "X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT"},
    {X509_V_ERR_SELF_SIGNED_CERT_IN_CHAIN,
     "X509_V_ERR_SELF_SIGNED_CERT_IN_CHAIN"},
    {X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT_LOCALLY,
     "X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT_LOCALLY"},
    {X509_V_ERR_UNABLE_TO_VERIFY_LEAF_SIGNATURE,
     "X509_V_ERR_UNABLE_TO_VERIFY_LEAF_SIGNATURE"},
    {X509_V_ERR_CERT_CHAIN_TOO_LONG,
     "X509_V_ERR_CERT_CHAIN_TOO_LONG"},
    {X509_V_ERR_CERT_REVOKED,
     "X509_V_ERR_CERT_REVOKED"},
    {X509_V_ERR_INVALID_CA,
     "X509_V_ERR_INVALID_CA"},
    {X509_V_ERR_PATH_LENGTH_EXCEEDED,
     "X509_V_ERR_PATH_LENGTH_EXCEEDED"},
    {X509_V_ERR_INVALID_PURPOSE,
     "X509_V_ERR_INVALID_PURPOSE"},
    {X509_V_ERR_CERT_UNTRUSTED,
     "X509_V_ERR_CERT_UNTRUSTED"},
    {X509_V_ERR_CERT_REJECTED,
     "X509_V_ERR_CERT_REJECTED"},
    {X509_V_ERR_SUBJECT_ISSUER_MISMATCH,
     "X509_V_ERR_SUBJECT_ISSUER_MISMATCH"},
    {X509_V_ERR_AKID_SKID_MISMATCH,
     "X509_V_ERR_AKID_SKID_MISMATCH"},
    {X509_V_ERR_AKID_ISSUER_SERIAL_MISMATCH,
     "X509_V_ERR_AKID_ISSUER_SERIAL_MISMATCH"},
    {X509_V_ERR_KEYUSAGE_NO_CERTSIGN,
     "X509_V_ERR_KEYUSAGE_NO_CERTSIGN"},
    {X509_V_ERR_APPLICATION_VERIFICATION,
     "X509_V_ERR_APPLICATION_VERIFICATION"},
    { SSL_ERROR_NONE, "SSL_ERROR_NONE"},
    {SSL_ERROR_NONE, NULL}
};

static void loadSslErrorMap()
{
    assert(TheSslErrors.empty());
    for (int i = 0; TheSslErrorArray[i].name; ++i) {
        TheSslErrors[TheSslErrorArray[i].value] = &TheSslErrorArray[i];
    }
}

Ssl::ssl_error_t Ssl::GetErrorCode(const char *name)
{
    //TODO: use a std::map?
    for (int i = 0; TheSslErrorArray[i].name != NULL; ++i) {
        if (strcmp(name, TheSslErrorArray[i].name) == 0)
            return TheSslErrorArray[i].value;
    }
    return SSL_ERROR_NONE;
}

Ssl::ssl_error_t
Ssl::ParseErrorString(const char *name)
{
    assert(name);

    const Ssl::ssl_error_t ssl_error = GetErrorCode(name);
    if (ssl_error != SSL_ERROR_NONE)
        return ssl_error;

    if (xisdigit(*name)) {
        const long int value = strtol(name, NULL, 0);
        if (SQUID_SSL_ERROR_MIN <= value && value <= SQUID_SSL_ERROR_MAX)
            return value;
        fatalf("Too small or too bug SSL error code '%s'", name);
    }

    fatalf("Unknown SSL error name '%s'", name);
    return SSL_ERROR_SSL; // not reached
}

const char *Ssl::GetErrorName(Ssl::ssl_error_t value)
{
    if (TheSslErrors.empty())
        loadSslErrorMap();

    const SslErrors::const_iterator it = TheSslErrors.find(value);
    if (it != TheSslErrors.end())
        return it->second->name;

    return NULL;
}

const char *
Ssl::GetErrorDescr(Ssl::ssl_error_t value)
{
    return ErrorDetailsManager::GetInstance().getDefaultErrorDescr(value);
}

Ssl::ErrorDetail::err_frm_code Ssl::ErrorDetail::ErrorFormatingCodes[] = {
    {"ssl_subject", &Ssl::ErrorDetail::subject},
    {"ssl_ca_name", &Ssl::ErrorDetail::ca_name},
    {"ssl_cn", &Ssl::ErrorDetail::cn},
    {"ssl_notbefore", &Ssl::ErrorDetail::notbefore},
    {"ssl_notafter", &Ssl::ErrorDetail::notafter},
    {"err_name", &Ssl::ErrorDetail::err_code},
    {"ssl_error_descr", &Ssl::ErrorDetail::err_descr},
    {"ssl_lib_error", &Ssl::ErrorDetail::err_lib_error},
    {NULL,NULL}
};

/**
 * The subject of the current certification in text form
 */

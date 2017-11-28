#include "squid.h"
#include "ssl/ErrorDetail.h"

struct SslErrorDetailEntry {
    Ssl::ssl_error_t value;
    const char *name;
    const char *detail;
};

static const char *SslErrorDetailDefaultStr = "SSL certificate validation error (%err_name): %ssl_subject";
// TODO: optimize by replacing with std::map or similar
static SslErrorDetailEntry TheSslDetailMap[] = {
    {  SQUID_X509_V_ERR_DOMAIN_MISMATCH,
        "SQUID_X509_V_ERR_DOMAIN_MISMATCH",
        "%err_name: The hostname you are connecting to (%H),  does not match any of the Certificate valid names: %ssl_cn"},
    { X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT,
      "X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT",
      "%err_name: SSL Certficate error: certificate issuer (CA) not known: %ssl_ca_name" },
    { X509_V_ERR_CERT_NOT_YET_VALID,
      "X509_V_ERR_CERT_NOT_YET_VALID",
      "%err_name: SSL Certficate is not valid before: %ssl_notbefore" },
    { X509_V_ERR_ERROR_IN_CERT_NOT_BEFORE_FIELD,
      "X509_V_ERR_ERROR_IN_CERT_NOT_BEFORE_FIELD",
      "%err_name: SSL Certificate has invalid start date (the 'not before' field): %ssl_subject" },
    { X509_V_ERR_CERT_HAS_EXPIRED,
      "X509_V_ERR_CERT_HAS_EXPIRED",
      "%err_name: SSL Certificate expired on %ssl_notafter" },
    { X509_V_ERR_ERROR_IN_CERT_NOT_AFTER_FIELD,
      "X509_V_ERR_ERROR_IN_CERT_NOT_AFTER_FIELD",
      "%err_name: SSL Certificate has invalid expiration date (the 'not after' field): %ssl_subject" },
    {X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT,
     "X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT",
     "%err_name: Self-signed SSL Certificate: %ssl_subject"},
    { X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT_LOCALLY,
      "X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT_LOCALLY",
      "%err_name: SSL Certficate error: certificate issuer (CA) not known: %ssl_ca_name" },
    { SSL_ERROR_NONE, "SSL_ERROR_NONE", "%err_name: No error" },
    {SSL_ERROR_NONE, NULL, NULL }
};

Ssl::ssl_error_t
Ssl::parseErrorString(const char *name)
{
    assert(name);

    for (int i = 0; TheSslDetailMap[i].name; ++i) {
        if (strcmp(name, TheSslDetailMap[i].name) == 0)
            return TheSslDetailMap[i].value;
    }

    if (xisdigit(*name)) {
        const long int value = strtol(name, NULL, 0);
        if (SQUID_SSL_ERROR_MIN <= value && value <= SQUID_SSL_ERROR_MAX)
            return value;
        fatalf("Too small or too bug SSL error code '%s'", name);
    }

    fatalf("Unknown SSL error name '%s'", name);
    return SSL_ERROR_SSL; // not reached
}

const char *
Ssl::getErrorName(Ssl::ssl_error_t value)
{

    for (int i = 0; TheSslDetailMap[i].name; ++i) {
        if (TheSslDetailMap[i].value == value)
            return TheSslDetailMap[i].name;
    }

    return NULL;
}

static const char *getErrorDetail(Ssl::ssl_error_t value)
{
    for (int i = 0; TheSslDetailMap[i].name; ++i) {
        if (TheSslDetailMap[i].value == value)
            return TheSslDetailMap[i].detail;
    }

    // we must always return something because ErrorDetail::buildDetail
    // will hit an assertion
    return SslErrorDetailDefaultStr;
}

Ssl::ErrorDetail::err_frm_code Ssl::ErrorDetail::ErrorFormatingCodes[] = {
    {"ssl_subject", &Ssl::ErrorDetail::subject},
    {"ssl_ca_name", &Ssl::ErrorDetail::ca_name},
    {"ssl_cn", &Ssl::ErrorDetail::cn},
    {"ssl_notbefore", &Ssl::ErrorDetail::notbefore},
    {"ssl_notafter", &Ssl::ErrorDetail::notafter},
    {"err_name", &Ssl::ErrorDetail::err_code},
    {NULL,NULL}
};

/**
 * The subject of the current certification in text form
 */

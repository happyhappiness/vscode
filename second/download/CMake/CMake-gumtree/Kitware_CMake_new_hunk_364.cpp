
#include "curl_setup.h"

#if !defined(CURL_DISABLE_HTTP) && defined(USE_SPNEGO)

#include "urldata.h"
#include "sendf.h"
#include "rawstr.h"
#include "http_negotiate.h"
#include "vauth/vauth.h"

/* The last 3 #include files should be in this order */
#include "curl_printf.h"
#include "curl_memory.h"
#include "memdebug.h"

CURLcode Curl_input_negotiate(struct connectdata *conn, bool proxy,
                              const char *header)
{
  struct Curl_easy *data = conn->data;
  size_t len;

  /* Point to the username, password, service and host */
  const char *userp;
  const char *passwdp;
  const char *service;
  const char *host;

  /* Point to the correct struct with this */
  struct negotiatedata *neg_ctx;

  if(proxy) {
    userp = conn->proxyuser;
    passwdp = conn->proxypasswd;
    service = data->set.str[STRING_PROXY_SERVICE_NAME] ?
              data->set.str[STRING_PROXY_SERVICE_NAME] : "HTTP";
    host = conn->proxy.name;
    neg_ctx = &data->state.proxyneg;
  }
  else {
    userp = conn->user;
    passwdp = conn->passwd;
    service = data->set.str[STRING_SERVICE_NAME] ?
              data->set.str[STRING_SERVICE_NAME] : "HTTP";
    host = conn->host.name;
    neg_ctx = &data->state.negotiate;
  }

  /* Not set means empty */
  if(!userp)
    userp = "";

  if(!passwdp)
    passwdp = "";

  /* Obtain the input token, if any */
  header += strlen("Negotiate");
  while(*header && ISSPACE(*header))
    header++;

  len = strlen(header);
  if(!len) {
    /* Is this the first call in a new negotiation? */
    if(neg_ctx->context) {
      /* The server rejected our authentication and hasn't suppled any more
      negotiation mechanisms */
      return CURLE_LOGIN_DENIED;
    }
  }

  /* Initilise the security context and decode our challenge */
  return Curl_auth_decode_spnego_message(data, userp, passwdp, service, host,
                                         header, neg_ctx);
}

CURLcode Curl_output_negotiate(struct connectdata *conn, bool proxy)
{
  struct negotiatedata *neg_ctx = proxy ? &conn->data->state.proxyneg :
    &conn->data->state.negotiate;
  char *base64 = NULL;
  size_t len = 0;
  char *userp;
  CURLcode result;

  result = Curl_auth_create_spnego_message(conn->data, neg_ctx, &base64, &len);
  if(result)
    return result;

  userp = aprintf("%sAuthorization: Negotiate %s\r\n", proxy ? "Proxy-" : "",
                  base64);

  if(proxy) {
    Curl_safefree(conn->allocptr.proxyuserpwd);
    conn->allocptr.proxyuserpwd = userp;

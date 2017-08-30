

#include "curl_setup.h"



#if defined(HAVE_GSSAPI) && !defined(CURL_DISABLE_HTTP) && defined(USE_SPNEGO)



#include "urldata.h"

#include "sendf.h"

#include "curl_gssapi.h"

#include "rawstr.h"

#include "curl_base64.h"

#include "http_negotiate.h"

#include "curl_sasl.h"

#include "url.h"

#include "curl_printf.h"



/* The last #include files should be: */

#include "curl_memory.h"

#include "memdebug.h"



CURLcode Curl_input_negotiate(struct connectdata *conn, bool proxy,

                              const char *header)

{

  struct SessionHandle *data = conn->data;

  struct negotiatedata *neg_ctx = proxy?&data->state.proxyneg:

    &data->state.negotiate;

  OM_uint32 major_status, minor_status, discard_st;

  gss_buffer_desc spn_token = GSS_C_EMPTY_BUFFER;

  gss_buffer_desc input_token = GSS_C_EMPTY_BUFFER;

  gss_buffer_desc output_token = GSS_C_EMPTY_BUFFER;

  size_t len;

  size_t rawlen = 0;

  CURLcode result;



  if(neg_ctx->context && neg_ctx->status == GSS_S_COMPLETE) {

    /* We finished successfully our part of authentication, but server

     * rejected it (since we're again here). Exit with an error since we

     * can't invent anything better */

    Curl_cleanup_negotiate(data);

    return CURLE_LOGIN_DENIED;

  }



  if(!neg_ctx->server_name) {

    /* Generate our SPN */

    char *spn = Curl_sasl_build_gssapi_spn(

      proxy ? data->set.str[STRING_PROXY_SERVICE_NAME] :

      data->set.str[STRING_SERVICE_NAME],

      proxy ? conn->proxy.name : conn->host.name);

    if(!spn)

      return CURLE_OUT_OF_MEMORY;



    /* Populate the SPN structure */

    spn_token.value = spn;

    spn_token.length = strlen(spn);



    /* Import the SPN */

    major_status = gss_import_name(&minor_status, &spn_token,

                                   GSS_C_NT_HOSTBASED_SERVICE,

                                   &neg_ctx->server_name);

    if(GSS_ERROR(major_status)) {

      Curl_gss_log_error(data, minor_status, "gss_import_name() failed: ");



      free(spn);



      return CURLE_OUT_OF_MEMORY;

    }



    free(spn);

  }



  header += strlen("Negotiate");

  while(*header && ISSPACE(*header))

    header++;



  len = strlen(header);

  if(len > 0) {

    result = Curl_base64_decode(header, (unsigned char **)&input_token.value,

                                &rawlen);

    if(result)

      return result;



    if(!rawlen) {

      infof(data, "Negotiate handshake failure (empty challenge message)\n");



      return CURLE_BAD_CONTENT_ENCODING;

    }



    input_token.length = rawlen;



    DEBUGASSERT(input_token.value != NULL);


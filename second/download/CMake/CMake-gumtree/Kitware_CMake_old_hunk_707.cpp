

#include "curl_setup.h"



#ifdef HAVE_GSSAPI

#ifdef HAVE_OLD_GSSMIT

#define GSS_C_NT_HOSTBASED_SERVICE gss_nt_service_name

#define NCOMPAT 1

#endif



#ifndef CURL_DISABLE_HTTP



#include "urldata.h"

#include "sendf.h"

#include "curl_gssapi.h"

#include "rawstr.h"

#include "curl_base64.h"

#include "http_negotiate.h"

#include "curl_memory.h"

#include "url.h"



#define _MPRINTF_REPLACE /* use our functions only */

#include <curl/mprintf.h>



/* The last #include file should be: */

#include "memdebug.h"



static int

get_gss_name(struct connectdata *conn, bool proxy, gss_name_t *server)

{

  OM_uint32 major_status, minor_status;

  gss_buffer_desc token = GSS_C_EMPTY_BUFFER;

  char name[2048];

  const char* service = "HTTP";



  token.length = strlen(service) + 1 + strlen(proxy ? conn->proxy.name :

                                              conn->host.name) + 1;

  if(token.length + 1 > sizeof(name))

    return EMSGSIZE;



  snprintf(name, sizeof(name), "%s@%s", service, proxy ? conn->proxy.name :

           conn->host.name);



  token.value = (void *) name;

  major_status = gss_import_name(&minor_status,

                                 &token,

                                 GSS_C_NT_HOSTBASED_SERVICE,

                                 server);



  return GSS_ERROR(major_status) ? -1 : 0;

}



static void

log_gss_error(struct connectdata *conn, OM_uint32 error_status,

              const char *prefix)

{

  OM_uint32 maj_stat, min_stat;

  OM_uint32 msg_ctx = 0;

  gss_buffer_desc status_string;

  char buf[1024];

  size_t len;



  snprintf(buf, sizeof(buf), "%s", prefix);

  len = strlen(buf);

  do {

    maj_stat = gss_display_status(&min_stat,

                                  error_status,

                                  GSS_C_MECH_CODE,

                                  GSS_C_NO_OID,

                                  &msg_ctx,

                                  &status_string);

      if(sizeof(buf) > len + status_string.length + 1) {

        snprintf(buf + len, sizeof(buf) - len,

                 ": %s", (char*) status_string.value);

      len += status_string.length;

    }

    gss_release_buffer(&min_stat, &status_string);

  } while(!GSS_ERROR(maj_stat) && msg_ctx != 0);



  infof(conn->data, "%s\n", buf);

}



/* returning zero (0) means success, everything else is treated as "failure"

   with no care exactly what the failure was */

int Curl_input_negotiate(struct connectdata *conn, bool proxy,

                         const char *header)

{

  struct SessionHandle *data = conn->data;

  struct negotiatedata *neg_ctx = proxy?&data->state.proxyneg:

    &data->state.negotiate;

  OM_uint32 major_status, minor_status, discard_st;

  gss_buffer_desc input_token = GSS_C_EMPTY_BUFFER;

  gss_buffer_desc output_token = GSS_C_EMPTY_BUFFER;

  int ret;

  size_t len;

  size_t rawlen = 0;

  CURLcode error;



  if(neg_ctx->context && neg_ctx->status == GSS_S_COMPLETE) {

    /* We finished successfully our part of authentication, but server

     * rejected it (since we're again here). Exit with an error since we

     * can't invent anything better */

    Curl_cleanup_negotiate(data);

    return -1;

  }



  if(neg_ctx->server_name == NULL &&

      (ret = get_gss_name(conn, proxy, &neg_ctx->server_name)))

    return ret;



  header += strlen("Negotiate");

  while(*header && ISSPACE(*header))

    header++;



  len = strlen(header);

  if(len > 0) {

    error = Curl_base64_decode(header,

                               (unsigned char **)&input_token.value, &rawlen);

    if(error || rawlen == 0)

      return -1;

    input_token.length = rawlen;



    DEBUGASSERT(input_token.value != NULL);


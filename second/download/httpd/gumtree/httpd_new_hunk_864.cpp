                                  I couldn't give it up because by that
                                  time I was too famous.''
                                            -- Unknown                */
#include "mod_ssl.h"

/*
 *  Post Read Request Handler
 */
int ssl_hook_ReadReq(request_rec *r)
{
    SSLConnRec *sslconn = myConnConfig(r->connection);
    SSL *ssl;

bool
Ssl::ClientBio::isClientHello(int state)
{
    return (
#if defined(SSL2_ST_GET_CLIENT_HELLO_A)
               state == SSL2_ST_GET_CLIENT_HELLO_A ||
#endif
               state == SSL3_ST_SR_CLNT_HELLO_A ||
               state == SSL23_ST_SR_CLNT_HELLO_A ||
               state == SSL23_ST_SR_CLNT_HELLO_B ||
               state == SSL3_ST_SR_CLNT_HELLO_B ||
               state == SSL3_ST_SR_CLNT_HELLO_C
           );
}
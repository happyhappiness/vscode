const char *ssl_cmd_SSLSessionTickets(cmd_parms *cmd, void *dcfg, int flag)
{
    SSLSrvConfigRec *sc = mySrvConfig(cmd->server);
#ifndef SSL_OP_NO_TICKET
    return "This version of OpenSSL does not support using "
           "SSLSessionTickets.";
#endif
    sc->session_tickets = flag ? TRUE : FALSE;
    return NULL;
}
static int ssl_server_compatible(server_rec *s1, server_rec *s2)
{
    SSLSrvConfigRec *sc1 = s1? mySrvConfig(s1) : NULL;
    SSLSrvConfigRec *sc2 = s2? mySrvConfig(s2) : NULL;

    /* both use the same TLS protocol? */
    if (!sc1 || !sc2 
        || !ssl_ctx_compatible(sc1->server, sc2->server)) {
        return 0;
    }
    
    return 1;
}
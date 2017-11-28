static unsigned short
GetService(const char *proto)
{
    struct servent *port = NULL;
    /** Parses a port number or service name from the squid.conf */
    char *token = strtok(NULL, w_space);
    if (token == NULL) {
        self_destruct();
        return 0; /* NEVER REACHED */
    }
    /** Returns either the service port number from /etc/services */
    if ( !isUnsignedNumeric(token, strlen(token)) )
        port = getservbyname(token, proto);
    if (port != NULL) {
        return ntohs((unsigned short)port->s_port);
    }
    /** Or a numeric translation of the config text. */
    return xatos(token);
}
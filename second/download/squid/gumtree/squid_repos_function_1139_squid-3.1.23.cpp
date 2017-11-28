void
add_http_port(char *portspec)
{
    http_port_list *s = create_http_port(portspec);
    // we may need to merge better of the above returns a list with clones
    assert(s->next == NULL);
    s->next = cbdataReference(Config.Sockaddr.http);
    cbdataReferenceDone(Config.Sockaddr.http);
    Config.Sockaddr.http = cbdataReference(s);
}
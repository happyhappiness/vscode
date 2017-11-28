void
add_http_port(char *portspec)
{
    AnyP::PortCfg *s = new AnyP::PortCfg("http_port");
    parsePortSpecification(s, portspec);
    // we may need to merge better if the above returns a list with clones
    assert(s->next == NULL);
    s->next = cbdataReference(Config.Sockaddr.http);
    cbdataReferenceDone(Config.Sockaddr.http);
    Config.Sockaddr.http = cbdataReference(s);
}
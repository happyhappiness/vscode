void
add_http_port(char *portspec)
{
    AnyP::PortCfgPointer s = new AnyP::PortCfg();
    s->transport = parsePortProtocol(SBuf("HTTP"));
    parsePortSpecification(s, portspec);
    // we may need to merge better if the above returns a list with clones
    assert(s->next == NULL);
    s->next = HttpPortList;
    HttpPortList = s;
}
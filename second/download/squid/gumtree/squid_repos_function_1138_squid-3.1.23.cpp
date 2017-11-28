static http_port_list *
create_http_port(char *portspec)
{
    http_port_list *s = new http_port_list("http");
    parse_http_port_specification(s, portspec);
    return s;
}
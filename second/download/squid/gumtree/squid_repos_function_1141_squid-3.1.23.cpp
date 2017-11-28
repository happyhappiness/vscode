static void
parse_http_port_list(http_port_list ** head)
{
    char *token = strtok(NULL, w_space);

    if (!token) {
        self_destruct();
        return;
    }

    http_port_list *s = create_http_port(token);

    /* parse options ... */
    while ((token = strtok(NULL, w_space))) {
        parse_http_port_option(s, token);
    }

    if (Ip::EnableIpv6&IPV6_SPECIAL_SPLITSTACK && s->s.IsAnyAddr()) {
        // clone the port options from *s to *(s->next)
        s->next = cbdataReference(clone_http_port_list(s));
        s->next->s.SetIPv4();
        debugs(3, 3, "http(s)_port: clone wildcard address for split-stack: " << s->s << " and " << s->next->s);
    }

    while (*head)
        head = &(*head)->next;

    *head = cbdataReference(s);
}
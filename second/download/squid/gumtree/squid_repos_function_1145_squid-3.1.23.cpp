static void
parse_https_port_list(https_port_list ** head)
{
    char *token;
    https_port_list *s;

    token = strtok(NULL, w_space);

    if (!token)
        self_destruct();

    s = new https_port_list;
    parse_http_port_specification(&s->http, token);

    /* parse options ... */
    while ((token = strtok(NULL, w_space))) {
        parse_http_port_option(s, token);
    }

    while (*head) {
        http_port_list ** headTmp = &(*head)->http.next;
        head = (https_port_list **)headTmp;
    }

    *head = s;
}
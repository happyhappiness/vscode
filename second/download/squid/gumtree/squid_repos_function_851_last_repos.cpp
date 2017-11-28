static void
parse_IpAddress_list(Ip::Address_list ** head)
{
    char *token;
    Ip::Address_list *s;
    Ip::Address ipa;

    while ((token = ConfigParser::NextToken())) {
        if (GetHostWithPort(token, &ipa)) {

            while (*head)
                head = &(*head)->next;

            s = static_cast<Ip::Address_list *>(xcalloc(1, sizeof(*s)));
            s->s = ipa;

            *head = s;
        } else {
            self_destruct();
            return;
        }
    }
}
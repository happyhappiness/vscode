static void
parse_IpAddress_list(IpAddress_list ** head)
{
    char *token;

    while ((token = strtok(NULL, w_space))) {
        parse_IpAddress_list_token(head, token);
    }
}
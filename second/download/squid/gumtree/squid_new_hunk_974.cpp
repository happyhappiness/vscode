
        storeAppendPrintf(entry, "\n");
    }
}

static void
parse_acl_tos(acl_tos ** head)
{
    unsigned int tos;           /* Initially uint for strtoui. Casted to tos_t before return */
    char *token = ConfigParser::NextToken();

    if (!token) {
        self_destruct();
        return;

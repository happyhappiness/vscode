void
ConfigParser::ParseString(String *var)
{
    char *token = strtok(NULL, w_space);

    if (token == NULL)
        self_destruct();

    var->reset(token);
}
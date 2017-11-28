static void
parse_removalpolicy(RemovalPolicySettings ** settings)
{
    if (*settings)
        free_removalpolicy(settings);

    *settings = new RemovalPolicySettings;

    parse_string(&(*settings)->type);

    parse_wordlist(&(*settings)->args);
}
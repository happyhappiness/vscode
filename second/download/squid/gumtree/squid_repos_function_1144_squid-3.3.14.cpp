static void
free_removalpolicy(RemovalPolicySettings ** settings)
{
    if (!*settings)
        return;

    free_string(&(*settings)->type);

    free_wordlist(&(*settings)->args);

    delete *settings;

    *settings = NULL;
}
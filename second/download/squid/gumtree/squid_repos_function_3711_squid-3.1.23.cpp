void
Adaptation::ServiceGroup::parse()
{
    ConfigParser::ParseString(&id);

    wordlist *names = NULL;
    ConfigParser::ParseWordList(&names);
    for (wordlist *i = names; i; i = i->next)
        services.push_back(i->key);
    wordlistDestroy(&names);
}
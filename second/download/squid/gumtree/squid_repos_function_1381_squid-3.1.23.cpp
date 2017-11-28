void
LoadableModulesConfigure(const wordlist *names)
{
    int count = 0;
    for (const wordlist *i = names; i; i = i->next, ++count)
        LoadModule(i->key);
    debugs(1, 1, "Squid plugin modules loaded: " << count);
}
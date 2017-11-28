void
HttpRequestMethod::Configure(SquidConfig &cfg)
{
#if 0 /* extension methods obsolete now that we have METHOD_OTHER always enabled */
    wordlist *w = cfg.ext_methods;

    while (w) {
        char *s;

        for (s = w->key; *s; s++)
            *s = xtoupper(*s);

        AddExtension(w->key);

        w = w->next;
    }
#endif
}
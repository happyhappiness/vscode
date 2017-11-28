static const char *
netdbPeerName(const char *name)
{
    const wordlist *w;

    for (w = peer_names; w; w = w->next) {
        if (!strcmp(w->key, name))
            return w->key;
    }

    return wordlistAdd(&peer_names, name);
}
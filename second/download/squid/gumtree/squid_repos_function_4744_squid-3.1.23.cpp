void
Ident::Close(int fdnotused, void *data)
{
    IdentStateData *state = (IdentStateData *)data;
    identCallback(state, NULL);
    comm_close(state->fd);
    hash_remove_link(ident_hash, (hash_link *) state);
    xfree(state->hash.key);
    cbdataFree(state);
}
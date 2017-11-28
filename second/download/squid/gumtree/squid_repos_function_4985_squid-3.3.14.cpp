void
Ident::Close(const CommCloseCbParams &params)
{
    IdentStateData *state = (IdentStateData *)params.data;
    identCallback(state, NULL);
    state->conn->close();
    hash_remove_link(ident_hash, (hash_link *) state);
    xfree(state->hash.key);
    cbdataFree(state);
}
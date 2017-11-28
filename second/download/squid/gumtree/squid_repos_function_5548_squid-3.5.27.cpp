void
Ident::Close(const CommCloseCbParams &params)
{
    IdentStateData *state = (IdentStateData *)params.data;
    state->deleteThis("connection closed");
}
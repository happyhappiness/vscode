void
Ident::Timeout(const CommTimeoutCbParams &io)
{
    debugs(30, 3, HERE << io.conn);
    IdentStateData *state = (IdentStateData *)io.data;
    state->deleteThis("timeout");
}
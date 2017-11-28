void
Ident::ClientAdd(IdentStateData * state, IDCB * callback, void *callback_data)
{
    IdentClient *c = (IdentClient *)xcalloc(1, sizeof(*c));
    IdentClient **C;
    c->callback = callback;
    c->callback_data = cbdataReference(callback_data);

    for (C = &state->clients; *C; C = &(*C)->next);
    *C = c;
}
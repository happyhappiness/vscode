void
Ident::identCallback(IdentStateData * state, char *result)
{
    IdentClient *client;

    if (result && *result == '\0')
        result = NULL;

    while ((client = state->clients)) {
        void *cbdata;
        state->clients = client->next;

        if (cbdataReferenceValidDone(client->callback_data, &cbdata))
            client->callback(result, cbdata);

        xfree(client);
    }
}
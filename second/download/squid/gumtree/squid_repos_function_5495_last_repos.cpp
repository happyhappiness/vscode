void
Ident::IdentStateData::notify(const char *result)
{
    while (IdentClient *client = clients) {
        void *cbdata;
        clients = client->next;

        if (cbdataReferenceValidDone(client->callback_data, &cbdata))
            client->callback(result, cbdata);

        xfree(client);
    }
}
void
MemObject::addClient(store_client *aClient)
{
    ++nclients;
    dlinkAdd(aClient, &aClient->node, &clients);
}
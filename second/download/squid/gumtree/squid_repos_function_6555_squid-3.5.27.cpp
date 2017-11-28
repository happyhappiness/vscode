void
esiRemoveFree (void *data)
{
    esiRemove *thisNode = (esiRemove *)data;
    debugs(86, 5, "esiRemoveFree " << thisNode);
}
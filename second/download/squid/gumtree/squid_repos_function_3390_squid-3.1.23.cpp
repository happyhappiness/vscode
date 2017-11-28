void
clientStreamFree(void *foo)
{
    clientStreamNode *thisObject = (clientStreamNode *)foo;

    debugs(87, 3, "Freeing clientStreamNode " << thisObject);

    thisObject->removeFromStream();
    thisObject->data = NULL;
}
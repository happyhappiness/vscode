void
urnStart(HttpRequest * r, StoreEntry * e)
{
    UrnState *anUrn = new UrnState();
    anUrn->start (r, e);
}
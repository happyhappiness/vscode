void
Store::Stats(StoreEntry * output)
{
    assert(output);
    Root().stat(*output);
}
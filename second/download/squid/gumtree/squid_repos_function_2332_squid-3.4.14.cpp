void
httpHeaderDestroyFieldsInfo(HttpHeaderFieldInfo * table, int count)
{
    int i;

    for (i = 0; i < count; ++i)
        table[i].name.clean();

    delete [] table;
}
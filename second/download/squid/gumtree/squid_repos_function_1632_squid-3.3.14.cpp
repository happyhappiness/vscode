static int
statObjectsOpenfdFilter(const StoreEntry * e)
{
    if (e->mem_obj == NULL)
        return 0;

    if (e->mem_obj->swapout.sio == NULL)
        return 0;

    return 1;
}
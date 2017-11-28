void
StoreController::transientsAbandon(StoreEntry &e)
{
    if (transients) {
        assert(e.mem_obj);
        if (e.mem_obj->xitTable.index >= 0)
            transients->abandon(e);
    }
}
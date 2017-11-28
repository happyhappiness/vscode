void
Transients::unlink(StoreEntry &e)
{
    if (e.mem_obj && e.mem_obj->xitTable.io == MemObject::ioWriting)
        abandon(e);
}
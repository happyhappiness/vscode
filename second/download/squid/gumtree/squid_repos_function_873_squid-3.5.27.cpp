void
Transients::disconnect(MemObject &mem_obj)
{
    if (mem_obj.xitTable.index >= 0) {
        assert(map);
        if (mem_obj.xitTable.io == MemObject::ioWriting) {
            map->abortWriting(mem_obj.xitTable.index);
        } else {
            assert(mem_obj.xitTable.io == MemObject::ioReading);
            map->closeForReading(mem_obj.xitTable.index);
        }
        locals->at(mem_obj.xitTable.index) = NULL;
        mem_obj.xitTable.index = -1;
        mem_obj.xitTable.io = MemObject::ioDone;
    }
}
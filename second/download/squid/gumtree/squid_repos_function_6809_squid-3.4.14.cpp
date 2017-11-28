void
MemPoolMeter::flush()
{
    alloc.level = 0;
    inuse.level = 0;
    idle.level = 0;
    gb_allocated.count = 0;
    gb_allocated.bytes = 0;
    gb_oallocated.count = 0;
    gb_oallocated.bytes = 0;
    gb_saved.count = 0;
    gb_saved.bytes = 0;
    gb_freed.count = 0;
    gb_freed.bytes = 0;
}
/*
 * local variables
 */
static std::stack<StoreEntry*> LateReleaseStack;
MemAllocator *StoreEntry::pool = NULL;

void
Store::Stats(StoreEntry * output)
{
    assert(output);
    Root().stat(*output);
}

// XXX: new/delete operators need to be replaced with MEMPROXY_CLASS
// definitions but doing so exposes bug 4370, and maybe 4354 and 4355
void *
StoreEntry::operator new (size_t bytecount)
{
    assert(bytecount == sizeof (StoreEntry));

    if (!pool) {
        pool = memPoolCreate ("StoreEntry", bytecount);
    }

    return pool->alloc();

void
StoreEntry::swapOutDecision(const MemObject::SwapOut::Decision &decision)
{
    // Abandon our transient entry if neither shared memory nor disk wants it.
    assert(mem_obj);
    mem_obj->swapout.decision = decision;
    transientsAbandonmentCheck();
}
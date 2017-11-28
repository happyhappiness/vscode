void
Store::Controller::updateLimits()
{
    swapDir->updateLimits();

    store_swap_high = (long) (((float) maxSize() *
                               (float) Config.Swap.highWaterMark) / (float) 100);
    store_swap_low = (long) (((float) maxSize() *
                              (float) Config.Swap.lowWaterMark) / (float) 100);
    store_pages_max = Config.memMaxSize / sizeof(mem_node);

    // TODO: move this into a memory cache class when we have one
    const int64_t memMax = static_cast<int64_t>(min(Config.Store.maxInMemObjSize, Config.memMaxSize));
    const int64_t disksMax = swapDir ? swapDir->maxObjectSize() : 0;
    store_maxobjsize = std::max(disksMax, memMax);
}
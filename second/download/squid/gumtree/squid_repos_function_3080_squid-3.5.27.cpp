void
storeConfigure(void)
{
    store_swap_high = (long) (((float) Store::Root().maxSize() *
                               (float) Config.Swap.highWaterMark) / (float) 100);
    store_swap_low = (long) (((float) Store::Root().maxSize() *
                              (float) Config.Swap.lowWaterMark) / (float) 100);
    store_pages_max = Config.memMaxSize / sizeof(mem_node);

    store_maxobjsize = storeCalcMaxObjSize();
}
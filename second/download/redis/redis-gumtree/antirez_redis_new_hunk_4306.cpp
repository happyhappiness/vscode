    assert(key->storage == REDIS_VM_MEMORY);
    assert(key->refcount == 1);
    if (vmFindContiguousPages(&page,pages) == REDIS_ERR) return REDIS_ERR;
    if (vmWriteObjectOnSwap(val,page) == REDIS_ERR) return REDIS_ERR;
    key->vm.page = page;
    key->vm.usedpages = pages;
    key->storage = REDIS_VM_SWAPPED;

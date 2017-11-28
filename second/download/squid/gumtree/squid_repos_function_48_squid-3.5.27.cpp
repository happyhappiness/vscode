void * memAllocate(mem_type type)
{
    // let's waste plenty of memory. This should cover any possible need
    return xmalloc(64*1024);
}
void *apr_atomic_casptr(volatile void **mem_ptr,
                        void *swap_ptr,
                        const void *cmp_ptr)
{
     __csg(&cmp_ptr,     /* automatically updated from mem on __csg failure  */
           mem_ptr,      /* set from swap when __csg succeeds                */
           &swap_ptr);  
     return (void *)cmp_ptr;
}
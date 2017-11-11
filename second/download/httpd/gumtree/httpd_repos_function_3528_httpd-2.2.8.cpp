void *apr_atomic_casptr(volatile void **mem_ptr,
                        void *swap_ptr,
                        const void *cmp_ptr)
{
     __cs1(&cmp_ptr,     /* automatically updated from mem on __cs1 failure  */
           mem_ptr,      /* set from swap when __cs1 succeeds                */
           &swap_ptr);
     return (void *)cmp_ptr;
}
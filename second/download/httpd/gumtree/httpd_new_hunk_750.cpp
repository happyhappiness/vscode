{
    apr_pool_t *p;
    TSort *pSort;
    apr_array_header_t *pNew;
    int n;

    apr_pool_create(&p, apr_hook_global_pool);
    pSort=prepare(p,(TSortData *)pHooks->elts,pHooks->nelts);
    pSort=tsort(pSort,pHooks->nelts);
    pNew=apr_array_make(apr_hook_global_pool,pHooks->nelts,sizeof(TSortData));
    if(apr_hook_debug_enabled)
	printf("Sorting %s:",szName);
    for(n=0 ; pSort ; pSort=pSort->pNext,++n) {
	TSortData *pHook;
	assert(n < pHooks->nelts);
	pHook=apr_array_push(pNew);
	memcpy(pHook,pSort->pData,sizeof *pHook);
	if(apr_hook_debug_enabled)
	    printf(" %s",pHook->szName);
    }
    if(apr_hook_debug_enabled)
	fputc('\n',stdout);
    return pNew;
}

static apr_array_header_t *s_aHooksToSort;
typedef struct

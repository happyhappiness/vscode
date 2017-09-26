	memcpy(pHook,pSort->pData,sizeof *pHook);
	if(apr_hook_debug_enabled)
	    printf(" %s",pHook->szName);
    }
    if(apr_hook_debug_enabled)
	fputc('\n',stdout);
    return pNew;
}

#ifndef NETWARE
static apr_array_header_t *s_aHooksToSort;
#endif

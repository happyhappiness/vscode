    }
    s_aHooksToSort=NULL;
    s_phOptionalHooks=NULL;
    s_phOptionalFunctions=NULL;
}

APU_DECLARE(void) apr_show_hook(const char *szName,const char * const *aszPre,
			       const char * const *aszSucc)
{
    int nFirst;

    printf("  Hooked %s",szName);
    if(aszPre) {
	fputs(" pre(",stdout);

static int NXSeedRandomInternal( size_t width, void *seed )
{
    static int init = 0;
    int                        *s = (int *) seed;
    union { int x; char y[4]; } u;

    if (!init) {
        srand(NXGetSystemTick());
        init = 1;
    }
 
    if (width > 3)
    {
        do
        {
            *s++ = rand();
        }
        while ((width -= 4) > 3);
    }
 
    if (width > 0)
    {
        char *p = (char *) s;

        u.x = rand();
 
        while (width > 0)
           *p++ = u.y[width--];
    }
 
    return APR_SUCCESS;
}
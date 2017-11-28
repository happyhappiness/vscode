void
Mem::Init(void)
{
    /* all pools are ready to be used */
    static bool MemIsInitialized = false;
    if (MemIsInitialized)
        return;

    /** \par
     * NOTE: Mem::Init() is called before the config file is parsed
     * and before the debugging module has been initialized.  Any
     * debug messages here at level 0 or 1 will always be printed
     * on stderr.
     */

    /**
     * Then initialize all pools.
     * \par
     * Starting with generic 2kB - 64kB buffr pools, then specific object types.
     * \par
     * It does not hurt much to have a lot of pools since sizeof(MemPool) is
     * small; someday we will figure out what to do with all the entries here
     * that are never used or used only once; perhaps we should simply use
     * malloc() for those? @?@
     */
    memDataInit(MEM_2K_BUF, "2K Buffer", 2048, 10, false);
    memDataInit(MEM_4K_BUF, "4K Buffer", 4096, 10, false);
    memDataInit(MEM_8K_BUF, "8K Buffer", 8192, 10, false);
    memDataInit(MEM_16K_BUF, "16K Buffer", 16384, 10, false);
    memDataInit(MEM_32K_BUF, "32K Buffer", 32768, 10, false);
    memDataInit(MEM_64K_BUF, "64K Buffer", 65536, 10, false);
    memDataInit(MEM_DREAD_CTRL, "dread_ctrl", sizeof(dread_ctrl), 0);
    memDataInit(MEM_DWRITE_Q, "dwrite_q", sizeof(dwrite_q), 0);
    memDataInit(MEM_MD5_DIGEST, "MD5 digest", SQUID_MD5_DIGEST_LENGTH, 0);
    GetPool(MEM_MD5_DIGEST)->setChunkSize(512 * 1024);

    MemIsInitialized = true;

    // finally register with the cache manager
    Mgr::RegisterAction("mem", "Memory Utilization", Mem::Stats, 0, 1);
}
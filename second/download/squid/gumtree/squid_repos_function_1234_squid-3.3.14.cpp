void
Mem::Init(void)
{
    int i;

    /** \par
     * NOTE: Mem::Init() is called before the config file is parsed
     * and before the debugging module has been initialized.  Any
     * debug messages here at level 0 or 1 will always be printed
     * on stderr.
     */

    /** \par
     * Set all pointers to null. */
    memset(MemPools, '\0', sizeof(MemPools));
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
    memDataInit(MEM_ACL_DENY_INFO_LIST, "AclDenyInfoList",
                sizeof(AclDenyInfoList), 0);
    memDataInit(MEM_ACL_NAME_LIST, "acl_name_list", sizeof(AclNameList), 0);
#if USE_CACHE_DIGESTS

    memDataInit(MEM_CACHE_DIGEST, "CacheDigest", sizeof(CacheDigest), 0);
#endif

    memDataInit(MEM_LINK_LIST, "link_list", sizeof(link_list), 10);
    memDataInit(MEM_DLINK_NODE, "dlink_node", sizeof(dlink_node), 10);
    memDataInit(MEM_DREAD_CTRL, "dread_ctrl", sizeof(dread_ctrl), 0);
    memDataInit(MEM_DWRITE_Q, "dwrite_q", sizeof(dwrite_q), 0);
    memDataInit(MEM_HTTP_HDR_CONTENT_RANGE, "HttpHdrContRange", sizeof(HttpHdrContRange), 0);
    memDataInit(MEM_NETDBENTRY, "netdbEntry", sizeof(netdbEntry), 0);
    memDataInit(MEM_NET_DB_NAME, "net_db_name", sizeof(net_db_name), 0);
    memDataInit(MEM_RELIST, "RegexList", sizeof(RegexList), 0);
    memDataInit(MEM_CLIENT_INFO, "ClientInfo", sizeof(ClientInfo), 0);
    memDataInit(MEM_MD5_DIGEST, "MD5 digest", SQUID_MD5_DIGEST_LENGTH, 0);
    MemPools[MEM_MD5_DIGEST]->setChunkSize(512 * 1024);

    /** Lastly init the string pools. */
    for (i = 0; i < mem_str_pool_count; ++i) {
        StrPools[i].pool = memPoolCreate(StrPoolsAttrs[i].name, StrPoolsAttrs[i].obj_size);
        StrPools[i].pool->zeroOnPush(false);

        if (StrPools[i].pool->objectSize() != StrPoolsAttrs[i].obj_size)
            debugs(13, DBG_IMPORTANT, "Notice: " << StrPoolsAttrs[i].name << " is " << StrPools[i].pool->objectSize() << " bytes instead of requested " << StrPoolsAttrs[i].obj_size << " bytes");
    }

    MemIsInitialized = true;
    /** \par
     * finally register with the cache manager */
    RegisterWithCacheManager();
}
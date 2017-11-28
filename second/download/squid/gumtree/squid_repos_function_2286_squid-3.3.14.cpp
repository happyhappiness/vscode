static void
idnsAddPathComponent(const char *buf)
{
    if (npc == npc_alloc) {
        int oldalloc = npc_alloc;
        sp *oldptr = searchpath;

        if (0 == npc_alloc)
            npc_alloc = 2;
        else
            npc_alloc <<= 1;

        searchpath = (sp *)xcalloc(npc_alloc, sizeof(*searchpath));

        if (oldptr && oldalloc)
            memcpy(searchpath, oldptr, oldalloc * sizeof(*searchpath));

        if (oldptr)
            safe_free(oldptr);
    }

    assert(npc < npc_alloc);
    strncpy(searchpath[npc].domain, buf, sizeof(searchpath[npc].domain)-1);
    searchpath[npc].domain[sizeof(searchpath[npc].domain)-1] = '\0';
    Tolower(searchpath[npc].domain);
    debugs(78, 3, "idnsAddPathComponent: Added domain #" << npc << ": " << searchpath[npc].domain);
    ++npc;
}
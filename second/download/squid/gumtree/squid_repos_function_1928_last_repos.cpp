static void
idnsFreeSearchpath(void)
{
    safe_free(searchpath);
    npc = npc_alloc = 0;
}
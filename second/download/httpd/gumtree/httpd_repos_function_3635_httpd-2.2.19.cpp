static void free_world(void)
{
    if (worldid) {
        FreeSid(worldid);
        worldid = NULL;
    }
}
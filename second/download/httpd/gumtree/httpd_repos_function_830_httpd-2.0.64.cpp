static void shmcb_get_header(void *shm_mem, SHMCBHeader **header)
{
    *header = (SHMCBHeader *)shm_mem;
    return;
}
void *

SharedMemory::get(ssize_t * shm_offset)
{
    char *aBuf = NULL;
    int i;

    for (i = 0; i < nbufs; ++i) {
        if (CBIT_TEST(inuse_map, i))
            continue;

        CBIT_SET(inuse_map, i);

        *shm_offset = i * SHMBUF_BLKSZ;

        aBuf = buf + (*shm_offset);

        break;
    }

    assert(aBuf);
    assert(aBuf >= buf);
    assert(aBuf < buf + (nbufs * SHMBUF_BLKSZ));
    ++diskd_stats.shmbuf_count;

    if (diskd_stats.max_shmuse < diskd_stats.shmbuf_count)
        diskd_stats.max_shmuse = diskd_stats.shmbuf_count;

    return aBuf;
}
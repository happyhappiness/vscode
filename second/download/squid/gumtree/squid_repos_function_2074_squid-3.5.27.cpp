int
StoreHashIndex::callback()
{
    int result = 0;
    int j;
    static int ndir = 0;

    do {
        j = 0;

        for (int i = 0; i < Config.cacheSwap.n_configured; ++i) {
            if (ndir >= Config.cacheSwap.n_configured)
                ndir = ndir % Config.cacheSwap.n_configured;

            int temp_result = store(ndir)->callback();

            ++ndir;

            j += temp_result;

            result += temp_result;

            if (j > 100)
                fatal ("too much io\n");
        }
    } while (j > 0);

    ++ndir;

    return result;
}
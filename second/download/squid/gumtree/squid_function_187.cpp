void
CossSwapDir::statfs(StoreEntry & sentry) const
{
    storeAppendPrintf(&sentry, "\n");
    storeAppendPrintf(&sentry, "Maximum Size: %" PRIu64 " KB\n", max_size);
    storeAppendPrintf(&sentry, "Current Size: %" PRIu64 " KB\n", cur_size);
    storeAppendPrintf(&sentry, "Percent Used: %0.2f%%\n",
                      (100.0 * (double)cur_size / (double)max_size) );
    storeAppendPrintf(&sentry, "Number of object collisions: %d\n", (int) numcollisions);
#if 0
    /* is this applicable? I Hope not .. */
    storeAppendPrintf(sentry, "Filemap bits in use: %d of %d (%d%%)\n",
                      SD->map->n_files_in_map, SD->map->max_n_files,
                      Math::intPercent(SD->map->n_files_in_map, SD->map->max_n_files));
#endif

    //    storeAppendPrintf(&sentry, "Pending operations: %d out of %d\n", io->aq.aq_numpending, MAX_ASYNCOP);
    storeAppendPrintf(&sentry, "Flags:");

    if (flags.selected)
        storeAppendPrintf(&sentry, " SELECTED");

    if (flags.read_only)
        storeAppendPrintf(&sentry, " READ-ONLY");

    storeAppendPrintf(&sentry, "\n");
}
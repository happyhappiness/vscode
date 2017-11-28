void
free_cachedir(SquidConfig::_cacheSwap * swap)
{
    int i;
    /* DON'T FREE THESE FOR RECONFIGURE */

    if (reconfiguring)
        return;

    for (i = 0; i < swap->n_configured; ++i) {
        /* TODO XXX this lets the swapdir free resources asynchronously
        * swap->swapDirs[i]->deactivate();
        * but there may be such a means already.
        * RBC 20041225
        */
        swap->swapDirs[i] = NULL;
    }

    safe_free(swap->swapDirs);
    swap->swapDirs = NULL;
    swap->n_allocated = 0;
    swap->n_configured = 0;
}
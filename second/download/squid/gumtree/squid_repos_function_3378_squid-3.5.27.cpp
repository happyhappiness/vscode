void
PconnPool::noteUses(int uses)
{
    if (uses >= PCONN_HIST_SZ)
        uses = PCONN_HIST_SZ - 1;

    ++hist[uses];
}
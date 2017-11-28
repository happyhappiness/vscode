void
SwapDir::updateSize(int64_t size, int sign)
{
    int64_t blks = (size + fs.blksize - 1) / fs.blksize;
    int64_t k = ((blks * fs.blksize) >> 10) * sign;
    cur_size += k;
    store_swap_size += k;

    if (sign > 0)
        n_disk_objects++;
    else if (sign < 0)
        n_disk_objects--;
}
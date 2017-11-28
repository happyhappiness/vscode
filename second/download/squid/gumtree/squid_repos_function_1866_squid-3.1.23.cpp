void
SwapDir::diskFull()
{
    if (cur_size >= max_size)
        return;

    max_size = cur_size;

    debugs(20, 1, "WARNING: Shrinking cache_dir #" << index << " to " << cur_size << " KB");
}
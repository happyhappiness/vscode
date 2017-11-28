int
Fs::Ufs::UFSSwapDir::validFileno(sfileno filn, int flag) const
{
    if (filn < 0)
        return 0;

    /*
     * If flag is set it means out-of-range file number should
     * be considered invalid.
     */
    if (flag)
        if (filn > map->capacity())
            return 0;

    return 1;
}
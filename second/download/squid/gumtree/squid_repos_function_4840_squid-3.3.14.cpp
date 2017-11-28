void
Rock::SwapDir::diskFull()
{
    debugs(20, DBG_IMPORTANT, "BUG: No space left with rock cache_dir: " <<
           filePath);
}
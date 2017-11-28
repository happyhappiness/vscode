void
filemapFreeMemory(fileMap * fm)
{
    safe_free(fm->file_map);
    safe_free(fm);
}
static void *sys_realloc(void *param, void *ptr, size_t size)
{
    return realloc(ptr, size);
}
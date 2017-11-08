static void *
z_alloc(void *opaque, uInt items, uInt size)
{
    return malloc(items * size);
}
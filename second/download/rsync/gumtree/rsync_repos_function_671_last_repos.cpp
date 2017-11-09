void ZLIB_INTERNAL zcfree (opaque, ptr)
    voidpf opaque;
    voidpf ptr;
{
    free(ptr);
    if (opaque) return; /* make compiler happy */
}
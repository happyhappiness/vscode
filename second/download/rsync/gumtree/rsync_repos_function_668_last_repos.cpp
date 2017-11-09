voidpf ZLIB_INTERNAL zcalloc (voidpf opaque, uInt items, uInt size)
{
    if (opaque) opaque = 0; /* to make compiler happy */
    return _halloc((long)items, size);
}
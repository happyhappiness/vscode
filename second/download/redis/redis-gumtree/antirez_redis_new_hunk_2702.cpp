    int16_t i16;
    int32_t i32;
    int64_t i64, ret = 0;
    printf("%02x\n", encoding);
    if (encoding == ZIP_INT_8B) {
        ret = ((char*)p)[0];
    } else if (encoding == ZIP_INT_16B) {
        memcpy(&i16,p,sizeof(i16));
        memrev16ifbe(&i16);
        ret = i16;


    if (a == b) return 0;
    if (a->encoding != REDIS_ENCODING_RAW) {
        ll2string(bufa,sizeof(bufa),(long) a->ptr);
        astr = bufa;
        bothsds = 0;
    } else {
        astr = a->ptr;
    }
    if (b->encoding != REDIS_ENCODING_RAW) {
        ll2string(bufb,sizeof(bufb),(long) b->ptr);
        bstr = bufb;
        bothsds = 0;
    } else {

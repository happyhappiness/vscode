
    printf("{status %u}",*p++);
    while(1) {
        if (p[0] == ZIP_END) {
            printf("{end}");
            break;
        } else {
            unsigned char e;

            l = zipDecodeLength(p);
            printf("{key %u}",l);
            p += zipEncodeLength(NULL,l);
            fwrite(p,l,1,stdout);
            p += l;

            l = zipDecodeLength(p);
            printf("{value %u}",l);
            p += zipEncodeLength(NULL,l);
            e = *p++;
            fwrite(p,l,1,stdout);
            p += l+e;

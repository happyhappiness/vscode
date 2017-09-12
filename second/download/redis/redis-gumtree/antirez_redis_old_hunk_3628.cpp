            l = zipmapDecodeLength(p);
            printf("{key %u}",l);
            p += zipmapEncodeLength(NULL,l);
            fwrite(p,l,1,stdout);
            p += l;

            l = zipmapDecodeLength(p);
            printf("{value %u}",l);
            p += zipmapEncodeLength(NULL,l);
            e = *p++;
            fwrite(p,l,1,stdout);
            p += l+e;
            if (e) {
                printf("[");

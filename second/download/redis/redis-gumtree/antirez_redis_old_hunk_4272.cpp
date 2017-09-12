            p += zipmapEncodeLength(NULL,l);
            e = *p++;
            fwrite(p,l,1,stdout);
            p += l;
            if (e) {
                printf("[");
                while(e--) printf(".");

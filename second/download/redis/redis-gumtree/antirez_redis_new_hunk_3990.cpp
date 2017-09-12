        if (entry.encoding == ZIP_ENC_RAW) {
            fwrite(p,entry.len,1,stdout);
        } else {
            printf("%lld", (long long) zipLoadInteger(p,entry.encoding));
        }
        printf("\n");
        p += entry.len;

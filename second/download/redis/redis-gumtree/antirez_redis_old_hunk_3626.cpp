        while (ziplistGet(p, &entry, &elen, &value)) {
            printf("Entry: ");
            if (entry) {
                fwrite(entry,elen,1,stdout);
            } else {
                printf("%lld", value);
            }

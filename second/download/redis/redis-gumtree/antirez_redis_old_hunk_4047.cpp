        while (ziplistGet(p, &entry, &elen, &value)) {
            if (entry && strncmp("foo", entry, elen) == 0) {
                printf("Delete foo\n");
                zl = ziplistDelete(zl, &p);
            } else {
                printf("Entry: ");
                if (entry) {

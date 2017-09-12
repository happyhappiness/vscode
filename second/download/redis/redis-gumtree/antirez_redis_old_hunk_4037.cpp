            } else {
                printf("%lld", value);
            }
            zl = ziplistDelete(zl, &p, ZIPLIST_HEAD);
            printf("\n");
        }
        printf("\n");

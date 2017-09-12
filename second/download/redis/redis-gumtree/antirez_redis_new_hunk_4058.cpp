        }
        printf("\n");
        ziplistRepr(zl);
    }

    printf("Compare strings with ziplist entries:\n");
    {
        zl = createList();
        p = ziplistIndex(zl, 0);
        if (!ziplistCompare(p,"hello",5)) {
            printf("ERROR\n");
            return;
        }
        if (ziplistCompare(p,"hella",5)) {
            printf("ERROR\n");
            return;
        }

        p = ziplistIndex(zl, 3);
        if (!ziplistCompare(p,"1024",4)) {
            printf("ERROR\n");
            return;
        }
        if (ziplistCompare(p,"1025",4)) {
            printf("ERROR\n");
            return;
        }
        printf("SUCCESS\n");
    }

    return 0;

        }

        printf("\n");
        return ziplistDelete(zl,&p);
    } else {
        printf("ERROR: Could not pop\n");
        exit(1);

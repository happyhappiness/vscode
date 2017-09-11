        }

        printf("\n");
        ziplistDeleteRange(zl,-1,1);
    } else {
        printf("ERROR: Could not pop\n");
        exit(1);

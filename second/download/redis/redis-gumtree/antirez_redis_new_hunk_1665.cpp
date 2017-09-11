        }
        printf("\n");
        ziplistRepr(zl);
        zfree(zl);
    }

    printf("Regression test for >255 byte strings:\n");

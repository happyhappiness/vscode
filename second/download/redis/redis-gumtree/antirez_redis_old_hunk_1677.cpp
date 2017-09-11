
    printf("Regression test deleting next to last entries:\n");
    {
        char v[3][257];
        zlentry e[3];
        size_t i;

        for (i = 0; i < (sizeof(v)/sizeof(v[0])); i++) {

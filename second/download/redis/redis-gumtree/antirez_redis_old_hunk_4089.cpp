    zipmapRepr(zm);
    zm = zipmapDel(zm,(unsigned char*) "new",3,NULL);
    zipmapRepr(zm);
    printf("\nPerform a direct lookup:\n");
    {
        unsigned char *value;

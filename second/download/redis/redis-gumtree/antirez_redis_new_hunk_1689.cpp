    printf("\n");
}

#define UNUSED(x) (void)(x)
int zipmapTest(int argc, char *argv[]) {
    unsigned char *zm;

    UNUSED(argc);
    UNUSED(argv);

    zm = zipmapNew();

    zm = zipmapSet(zm,(unsigned char*) "name",4, (unsigned char*) "foo",3,NULL);

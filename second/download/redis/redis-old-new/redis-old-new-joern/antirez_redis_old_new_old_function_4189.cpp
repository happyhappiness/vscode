int main(void) {
    unsigned char *zm;

    zm = zipmapNew();
    zm = zipmapSet(zm,(unsigned char*) "hello",5, (unsigned char*) "world!",6);
    zm = zipmapSet(zm,(unsigned char*) "foo",3, (unsigned char*) "bar",3);
    zm = zipmapSet(zm,(unsigned char*) "foo",3, (unsigned char*) "!",1);
    zipmapRepr(zm);
    zm = zipmapSet(zm,(unsigned char*) "foo",3, (unsigned char*) "12345",5);
    zipmapRepr(zm);
    zm = zipmapSet(zm,(unsigned char*) "new",3, (unsigned char*) "xx",2);
    zipmapRepr(zm);
    zm = zipmapDel(zm,(unsigned char*) "new",3,NULL);
    zipmapRepr(zm);
    return 0;
}
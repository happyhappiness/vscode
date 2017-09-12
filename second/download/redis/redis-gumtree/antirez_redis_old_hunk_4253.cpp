    printf("\n");
}

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
    printf("Iterate trought elements:\n");
    {
        unsigned char *i = zm+1;
        unsigned char *key, *value;
        unsigned int klen, vlen;

        while((i = zipmapNext(i,&key,&klen,&value,&vlen)) != NULL) {
            printf("%d:%.*s => %d:%.*s\n", klen, klen, key, vlen, vlen, value);
        }
    }
    return 0;
}

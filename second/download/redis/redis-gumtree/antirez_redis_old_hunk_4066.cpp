    return zl;
}

int main(int argc, char **argv) {
    unsigned char *zl, *p, *q, *entry;
    unsigned int elen;
    sds s;

    zl = createList();
    ziplistRepr(zl);


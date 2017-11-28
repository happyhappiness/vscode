unsigned int
hash4(const void *data, unsigned int size)
{
    const char *key = static_cast<const char *>(data);
    size_t loop;
    unsigned int h;
    size_t len;

#define HASH4a   h = (h << 5) - h + *key++;
#define HASH4b   h = (h << 5) + h + *key++;
#define HASH4 HASH4b

    h = 0;
    len = strlen(key);
    loop = len >> 3;
    switch (len & (8 - 1)) {
    case 0:
        break;
    case 7:
        HASH4;
    /* FALLTHROUGH */
    case 6:
        HASH4;
    /* FALLTHROUGH */
    case 5:
        HASH4;
    /* FALLTHROUGH */
    case 4:
        HASH4;
    /* FALLTHROUGH */
    case 3:
        HASH4;
    /* FALLTHROUGH */
    case 2:
        HASH4;
    /* FALLTHROUGH */
    case 1:
        HASH4;
    }
    while (loop) {
        --loop;
        HASH4;
        HASH4;
        HASH4;
        HASH4;
        HASH4;
        HASH4;
        HASH4;
        HASH4;
    }
    return h % size;
}
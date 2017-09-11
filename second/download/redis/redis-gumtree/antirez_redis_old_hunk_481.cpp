#define BITOP_XOR   2
#define BITOP_NOT   3

/* SETBIT key offset bitvalue */
void setbitCommand(client *c) {
    robj *o;
    char *err = "bit is not an integer or out of range";
    size_t bitoffset;
    int byte, bit;
    int byteval, bitval;
    long on;


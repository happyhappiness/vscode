/* Compare two string objects via strcmp() or alike.
 * Note that the objects may be integer-encoded. In such a case we
 * use snprintf() to get a string representation of the numbers on the stack
 * and compare the strings, it's much faster than calling getDecodedObject().
 *
 * Important note: if objects are not integer encoded, but binary-safe strings,
 * sdscmp() from sds.c will apply memcmp() so this function ca be considered
 * binary safe. */
static int compareStringObjects(robj *a, robj *b) {
    assert(a->type == REDIS_STRING && b->type == REDIS_STRING);
    char bufa[128], bufb[128], *astr, *bstr;

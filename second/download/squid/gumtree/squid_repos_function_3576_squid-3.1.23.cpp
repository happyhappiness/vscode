void
storeSwapTLVFree(tlv * n)
{
    tlv *t;

    while ((t = n) != NULL) {
        n = t->next;
        xfree(t->value);
        delete t;
    }
}
int
storeKeyHashCmp(const void *a, const void *b)
{
    const unsigned char *A = (const unsigned char *)a;
    const unsigned char *B = (const unsigned char *)b;
    int i;

    for (i = 0; i < SQUID_MD5_DIGEST_LENGTH; i++) {
        if (A[i] < B[i])
            return -1;

        if (A[i] > B[i])
            return 1;
    }

    return 0;
}
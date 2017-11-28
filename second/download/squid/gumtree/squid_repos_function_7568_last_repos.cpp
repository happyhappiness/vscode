void
encrypt(char *nachr, int decr)
{
    char (*schl)[KS] = decr ? schluessel + 15 : schluessel;
    char tmp[BS];
    int i;

    perm(tmp, nachr, IP, BS);

    for (i = 8; i--;) {
        crypt_main(tmp, tmp + BS2, *schl);
        if (decr)
            schl--;
        else
            schl++;
        crypt_main(tmp + BS2, tmp, *schl);
        if (decr)
            schl--;
        else
            schl++;
    }

    perm(nachr, tmp, EP, BS);
}
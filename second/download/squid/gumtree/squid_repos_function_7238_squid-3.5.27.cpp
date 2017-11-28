void
setkey(char *schl)
{
    char tmp1[IS];
    register unsigned int ls = 0x7efc;
    register int i, j, k;
    register int shval = 0;
    register char *akt_schl;

    memcpy(E, E0, KS);
    perm(tmp1, schl, PC1, IS);

    for (i = 0; i < 16; i++) {
        shval += 1 + (ls & 1);
        akt_schl = schluessel[i];
        for (j = 0; j < KS; j++) {
            if ((k = PC2[j]) >= IS2) {
                if ((k += shval) >= IS)
                    k = (k - IS2) % IS2 + IS2;
            } else if ((k += shval) >= IS2)
                k %= IS2;
            *akt_schl++ = tmp1[k];
        }
        ls >>= 1;
    }
}
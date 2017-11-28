char *
crypt(const char *wort, const char *salt)
{
    static char retkey[14];
    char key[BS + 2];
    char *k;
    int tmp, keybyte;
    int i, j;

    memset(key, 0, BS + 2);

    for (k = key, i = 0; i < BS; i++) {
        if (!(keybyte = *wort++))
            break;
        k += 7;
        for (j = 0; j < 7; j++, i++) {
            *--k = keybyte & 1;
            keybyte >>= 1;
        }
        k += 8;
    }

    setkey(key);
    memset(key, 0, BS + 2);

    for (k = E, i = 0; i < 2; i++) {
        retkey[i] = keybyte = *salt++;
        if (keybyte > 'Z')
            keybyte -= 'a' - 'Z' - 1;
        if (keybyte > '9')
            keybyte -= 'A' - '9' - 1;
        keybyte -= '.';

        for (j = 0; j < 6; j++, keybyte >>= 1, k++) {
            if (!(keybyte & 1))
                continue;
            tmp = *k;
            *k = k[24];
            k[24] = tmp;
        }
    }

    for (i = 0; i < 25; i++)
        encrypt(key, 0);

    for (k = key, i = 0; i < 11; i++) {
        for (j = keybyte = 0; j < 6; j++) {
            keybyte <<= 1;
            keybyte |= *k++;
        }

        keybyte += '.';
        if (keybyte > '9')
            keybyte += 'A' - '9' - 1;
        if (keybyte > 'Z')
            keybyte += 'a' - 'Z' - 1;
        retkey[i + 2] = keybyte;
    }

    retkey[i + 2] = 0;

    if (!retkey[1])
        retkey[1] = *retkey;

    return retkey;
}
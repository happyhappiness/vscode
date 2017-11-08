static int strcmplex(const char *str1, const char *str2)
{
    int i, n1, n2;

    if (str1 == NULL)
        return -1;
    if (str2 == NULL)
        return +1;
    n1 = strlen(str1);
    n2 = strlen(str2);
    if (n1 > n2)
        return 1;
    if (n1 < n2)
        return -1;
    for (i = 0; i < n1; i++) {
        if (str1[i] > str2[i])
            return 1;
        if (str1[i] < str2[i])
            return -1;
    }
    return 0;
}
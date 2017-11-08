static int ssl_expr_eval_strcmplex(char *cpNum1, char *cpNum2)
{
    int i, n1, n2;

    if (cpNum1 == NULL)
        return -1;
    if (cpNum2 == NULL)
        return +1;
    n1 = strlen(cpNum1);
    n2 = strlen(cpNum2);
    if (n1 > n2)
        return 1;
    if (n1 < n2)
        return -1;
    for (i = 0; i < n1; i++) {
        if (cpNum1[i] > cpNum2[i])
            return 1;
        if (cpNum1[i] < cpNum2[i])
            return -1;
    }
    return 0;
}
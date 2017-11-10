const char *flatten_count_chars(count_chars *cc, int space)
{
    int i, size;
    char *newval;

    size = 0;
    for (i = 0; i < cc->num; i++) {
        if (cc->vals[i]) {
            size += strlen(cc->vals[i]) + 1;
            if (space) {
              size++;
            }
        }
    }

    newval = (char*)malloc(size + 1);
    newval[0] = 0;

    for (i = 0; i < cc->num; i++) {
        if (cc->vals[i]) {
            strcat(newval, cc->vals[i]);
            if (space) {
                strcat(newval, " ");
            }
        }
    }

    return newval;
}
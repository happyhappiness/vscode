void insert_count_chars(count_chars *cc, const char *newval, int position)
{
    int i;

    for (i = cc->num; i > position; i--) {
        cc->vals[i] = cc->vals[i-1];
    }

    cc->vals[position] = newval;
    cc->num++;
}
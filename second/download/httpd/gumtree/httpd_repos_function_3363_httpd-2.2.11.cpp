void clear_count_chars(count_chars *cc)
{
    int i;
    for (i = 0; i < cc->num; i++) {
        cc->vals[i] = 0;
    }

    cc->num = 0;
}
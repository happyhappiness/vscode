void append_count_chars(count_chars *cc, count_chars *cctoadd)
{
    int i;
    for (i = 0; i < cctoadd->num; i++) {
        if (cctoadd->vals[i]) {
            push_count_chars(cc, cctoadd->vals[i]);
        }
    }
}
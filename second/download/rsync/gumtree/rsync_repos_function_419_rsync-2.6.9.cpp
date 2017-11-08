local void set_data_type(s)
    deflate_state *s;
{
    int n;

    for (n = 0; n < 9; n++)
        if (s->dyn_ltree[n].Freq != 0)
            break;
    if (n == 9)
        for (n = 14; n < 32; n++)
            if (s->dyn_ltree[n].Freq != 0)
                break;
    s->strm->data_type = (n == 32) ? Z_TEXT : Z_BINARY;
}
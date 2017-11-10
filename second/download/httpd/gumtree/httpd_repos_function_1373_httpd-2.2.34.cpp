static void put_int_flush_right(request_rec * r, int i, int field)
{
    if (field > 1 || i > 9)
        put_int_flush_right(r, i / 10, field - 1);
    if (i)
        ap_rputc('0' + i % 10, r);
    else
        ap_rputs("&nbsp;", r);
}
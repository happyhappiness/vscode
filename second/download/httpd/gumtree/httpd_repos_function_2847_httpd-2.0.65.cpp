static UCHAR randbyte_hrtimer()
{
    QWORD t1, t2;
    UCHAR byte;

    DosTmrQueryTime(&t1);
    DosSleep(5);
    DosTmrQueryTime(&t2);

    byte = (t2.ulLo - t1.ulLo) & 0xFF;
    byte ^= (t2.ulLo - t1.ulLo) >> 8;
    return byte;
}
void
align(int n)
{
    if ( bpos % n != 0 ) {
        int al;
        al = (bpos/n);
        bpos = bpos+(bpos-n*al);
    }
}
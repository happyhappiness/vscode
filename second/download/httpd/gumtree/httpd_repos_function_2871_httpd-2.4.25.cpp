static int in_list(h2_workers *workers, h2_mplx *m)
{
    h2_mplx *e;
    for (e = H2_MPLX_LIST_FIRST(&workers->mplxs); 
         e != H2_MPLX_LIST_SENTINEL(&workers->mplxs);
         e = H2_MPLX_NEXT(e)) {
        if (e == m) {
            return 1;
        }
    }
    return 0;
}
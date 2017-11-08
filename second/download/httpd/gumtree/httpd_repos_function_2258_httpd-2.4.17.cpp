static void reference(h2_mplx *m)
{
    apr_atomic_inc32(&m->refs);
}
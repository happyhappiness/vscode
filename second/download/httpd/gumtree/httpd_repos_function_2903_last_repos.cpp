void h2_ngn_shed_destroy(h2_ngn_shed *shed)
{
    ap_assert(apr_hash_count(shed->ngns) == 0);
}
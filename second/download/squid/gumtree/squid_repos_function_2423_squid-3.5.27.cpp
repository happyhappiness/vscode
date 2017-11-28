void
httpHeaderCalcMask(HttpHeaderMask * mask, http_hdr_type http_hdr_type_enums[], size_t count)
{
    size_t i;
    const int * enums = (const int *) http_hdr_type_enums;
    assert(mask && enums);
    assert(count < sizeof(*mask) * 8);  /* check for overflow */

    for (i = 0; i < count; ++i) {
        assert(!CBIT_TEST(*mask, enums[i]));    /* check for duplicates */
        CBIT_SET(*mask, enums[i]);
    }
}
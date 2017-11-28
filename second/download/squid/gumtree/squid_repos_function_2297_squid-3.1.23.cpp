void
httpHdrCcSetMaxAge(HttpHdrCc * cc, int max_age)
{
    assert(cc);
    cc->max_age = max_age;

    if (max_age >= 0)
        EBIT_SET(cc->mask, CC_MAX_AGE);
    else
        EBIT_CLR(cc->mask, CC_MAX_AGE);
}
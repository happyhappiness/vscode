void
parse_time_t(time_t * var)
{
    time_msec_t tval;
    parseTimeLine(&tval, T_SECOND_STR, false);
    *var = static_cast<time_t>(tval/1000);
}
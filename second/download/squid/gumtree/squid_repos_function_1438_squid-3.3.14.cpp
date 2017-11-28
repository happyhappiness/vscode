int64_t
Math::int64Percent(const int64_t a, const int64_t b)
{
    return b ? ((int64_t) (100.0 * a / b + 0.5)) : 0;
}
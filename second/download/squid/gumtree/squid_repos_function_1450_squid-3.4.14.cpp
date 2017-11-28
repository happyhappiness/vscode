int
Math::intPercent(const int a, const int b)
{
    return b ? ((int) (100.0 * a / b + 0.5)) : 0;
}
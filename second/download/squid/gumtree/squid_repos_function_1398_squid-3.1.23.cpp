static
_method_t &operator++ (_method_t &aMethod)
{
    int tmp = (int)aMethod;
    aMethod = (_method_t)(++tmp);
    return aMethod;
}
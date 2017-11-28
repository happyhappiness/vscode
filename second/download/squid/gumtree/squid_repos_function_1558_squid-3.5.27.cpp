static Http::MethodType &
operator++ (Http::MethodType &aMethod)
{
    int tmp = (int)aMethod;
    aMethod = (Http::MethodType)(++tmp);
    return aMethod;
}
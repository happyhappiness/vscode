err_type &operator++ (err_type &anErr)
{
    int tmp = (int)anErr;
    anErr = (err_type)(++tmp);
    return anErr;
}
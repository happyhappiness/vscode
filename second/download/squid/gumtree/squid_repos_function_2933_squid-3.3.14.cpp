log_type &operator++ (log_type &aLogType)
{
    int tmp = (int)aLogType;
    aLogType = (log_type)(++tmp);
    return aLogType;
}
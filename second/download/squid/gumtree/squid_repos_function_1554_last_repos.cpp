time_t
positiveTimeout(const time_t timeout)
{
    return max(static_cast<time_t>(1), timeout);
}
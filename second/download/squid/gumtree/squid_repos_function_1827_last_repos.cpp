static inline time_t
diffOrZero(const time_t larger, const time_t smaller)
{
    return (larger > smaller) ? (larger - smaller) : 0;
}
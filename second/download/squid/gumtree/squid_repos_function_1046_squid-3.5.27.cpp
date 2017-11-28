static bool
StrToInt(const char* str, long& number)
{
    assert(str != NULL);

    char* end;
    number = strtol(str, &end, 0);

    return (end != str) && (*end == '\0'); // returns true if string contains nothing except number
}
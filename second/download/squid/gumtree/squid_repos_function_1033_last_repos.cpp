void
String::append(char const *str)
{
    assert(str);
    append(str, strlen(str));
}
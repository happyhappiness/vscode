void
String::limitInit(const char *str, int len)
{
    clean(); // TODO: optimize to avoid cleaning the buffer we can use
    allocAndFill(str, len);
}
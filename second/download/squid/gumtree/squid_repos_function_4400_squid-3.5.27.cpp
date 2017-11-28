const char *objToString(unsigned char const *bytes, int len)
{
    static std::string buf;
    buf.clear();
    for (int i = 0; i < len; i++ ) {
        char tmp[3];
        snprintf(tmp, sizeof(tmp), "%.2x", bytes[i]);
        buf.append(tmp);
    }
    return buf.c_str();
}
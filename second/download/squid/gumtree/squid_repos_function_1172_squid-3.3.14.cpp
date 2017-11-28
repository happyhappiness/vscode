static bool
parseNamedIntList(const char *data, const String &name, Vector<int> &list)
{
    if (data && (strncmp(data, name.rawBuf(), name.size()) == 0)) {
        data += name.size();
        if (*data == '=') {
            while (true) {
                ++data;
                int value = 0;
                if (!StringToInt(data, value, &data, 10))
                    break;
                list.push_back(value);
                if (*data == '\0' || *data != ',')
                    break;
            }
        }
    }
    return data && *data == '\0';
}
static void
formatWithString(std::string &formatted, const std::string &value)
{
    size_t start_pos = 0;
    while ((start_pos = formatted.find("%s", start_pos)) != std::string::npos) {
        formatted.replace(start_pos, 2, value);
        start_pos += 2;
    }
}
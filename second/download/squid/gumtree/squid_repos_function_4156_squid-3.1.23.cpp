std::string Ssl::CrtdMessage::compose() const
{
    if (code.empty()) return std::string();
    char buffer[10];
    snprintf(buffer, sizeof(buffer), "%zd", body.length());
    return code + ' ' + buffer + ' ' + body;
}
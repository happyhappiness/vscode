void Ssl::CrtdMessage::parseBody(CrtdMessage::BodyParams & map, std::string & other_part) const
{
    other_part.clear();
    // Copy string for using it as temp buffer.
    std::string temp_body(body.c_str(), body.length());
    char * buffer = const_cast<char *>(temp_body.c_str());
    char * token = strtok(buffer, "\r\n");
    while (token != NULL) {
        std::string current_string(token);
        size_t equal_pos = current_string.find('=');
        if (equal_pos == std::string::npos) {
            size_t offset_body_part = token - temp_body.c_str();
            other_part = std::string(body.c_str() + offset_body_part, body.length() - offset_body_part);
            break;
        } else {
            std::string param(current_string.c_str(), current_string.c_str() + equal_pos);
            std::string value(current_string.c_str() + equal_pos + 1);
            map.insert(std::make_pair(param, value));
        }
        token = strtok(NULL, "\r\n");
    }
}
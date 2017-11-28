Ssl::CrtdMessage::ParseResult Ssl::CrtdMessage::parse(const char * buffer, size_t len)
{
    char const *current_pos = buffer;
    while (current_pos != buffer + len && state != END) {
        switch (state) {
        case BEFORE_CODE: {
            if (xisspace(*current_pos)) {
                current_pos++;
                break;
            }
            if (xisalpha(*current_pos)) {
                state = CODE;
                break;
            }
            clear();
            return ERROR;
        }
        case CODE: {
            if (xisalnum(*current_pos) || *current_pos == '_') {
                current_block += *current_pos;
                current_pos++;
                break;
            }
            if (xisspace(*current_pos)) {
                code = current_block;
                current_block.clear();
                state = BEFORE_LENGTH;
                break;
            }
            clear();
            return ERROR;
        }
        case BEFORE_LENGTH: {
            if (xisspace(*current_pos)) {
                current_pos++;
                break;
            }
            if (xisdigit(*current_pos)) {
                state = LENGTH;
                break;
            }
            clear();
            return ERROR;
        }
        case LENGTH: {
            if (xisdigit(*current_pos)) {
                current_block += *current_pos;
                current_pos++;
                break;
            }
            if (xisspace(*current_pos)) {
                body_size = atoi(current_block.c_str());
                current_block.clear();
                state = BEFORE_BODY;
                break;
            }
            clear();
            return ERROR;
        }
        case BEFORE_BODY: {
            if (body_size == 0) {
                state = END;
                break;
            }
            if (xisspace(*current_pos)) {
                current_pos++;
                break;
            } else {
                state = BODY;
                break;
            }
        }
        case BODY: {
            size_t body_len = (static_cast<size_t>(buffer + len - current_pos) >= body_size - current_block.length())
                              ? body_size - current_block.length()
                              : static_cast<size_t>(buffer + len - current_pos);
            current_block += std::string(current_pos, body_len);
            current_pos += body_len;
            if (current_block.length() == body_size) {
                body = current_block;
                state = END;
            }
            if (current_block.length() > body_size) {
                clear();
                return ERROR;
            }
            break;
        }
        case END: {
            return OK;
        }
        }
    }
    if (state != END) return INCOMPLETE;
    return OK;
}
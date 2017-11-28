const char *
base64_encode(const char *decoded_str)
{
    static char result[BASE64_RESULT_SZ];
    int bits = 0;
    int char_count = 0;
    int out_cnt = 0;
    int c;

    if (!decoded_str)
        return decoded_str;

    if (!base64_initialized)
        base64_init();

    while ((c = (unsigned char) *decoded_str++) && out_cnt < sizeof(result) - 5) {
        bits += c;
        char_count++;
        if (char_count == 3) {
            result[out_cnt++] = base64_code[bits >> 18];
            result[out_cnt++] = base64_code[(bits >> 12) & 0x3f];
            result[out_cnt++] = base64_code[(bits >> 6) & 0x3f];
            result[out_cnt++] = base64_code[bits & 0x3f];
            bits = 0;
            char_count = 0;
        } else {
            bits <<= 8;
        }
    }
    if (char_count != 0) {
        bits <<= 16 - (8 * char_count);
        result[out_cnt++] = base64_code[bits >> 18];
        result[out_cnt++] = base64_code[(bits >> 12) & 0x3f];
        if (char_count == 1) {
            result[out_cnt++] = '=';
            result[out_cnt++] = '=';
        } else {
            result[out_cnt++] = base64_code[(bits >> 6) & 0x3f];
            result[out_cnt++] = '=';
        }
    }
    result[out_cnt] = '\0';	/* terminate */
    return result;
}
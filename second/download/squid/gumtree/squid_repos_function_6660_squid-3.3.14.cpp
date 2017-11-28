int
base64_encode(char *result, int result_size, const char *data, int data_size)
{
    int bits = 0;
    int char_count = 0;
    int out_cnt = 0;

    if (!data || !*data || !result || result_size < 1 || data_size < 1)
        return 0;

    if (!base64_initialized)
        base64_init();

    while (data_size--) {
        int c = (unsigned char) *data++;
        bits += c;
        char_count++;
        if (char_count == 3) {
            if (out_cnt >= result_size)
                break;
            if (out_cnt+4 <= result_size) {
                result[out_cnt++] = base64_code[bits >> 18];
                result[out_cnt++] = base64_code[(bits >> 12) & 0x3f];
                result[out_cnt++] = base64_code[(bits >> 6) & 0x3f];
                result[out_cnt++] = base64_code[bits & 0x3f];
            } else {
                // part-quantum goes a bit slower with per-byte checks
                result[out_cnt++] = base64_code[bits >> 18];
                if (out_cnt >= result_size)
                    break;
                result[out_cnt++] = base64_code[(bits >> 12) & 0x3f];
                if (out_cnt >= result_size)
                    break;
                result[out_cnt++] = base64_code[(bits >> 6) & 0x3f];
                if (out_cnt >= result_size)
                    break;
                result[out_cnt++] = base64_code[bits & 0x3f];
            }
            bits = 0;
            char_count = 0;
        } else {
            bits <<= 8;
        }
    }
    if (char_count != 0) {
        bits <<= 16 - (8 * char_count);
        if (out_cnt >= result_size)
            return result_size;
        result[out_cnt++] = base64_code[bits >> 18];
        if (out_cnt >= result_size)
            return result_size;
        result[out_cnt++] = base64_code[(bits >> 12) & 0x3f];
        if (char_count == 1) {
            if (out_cnt >= result_size)
                return result_size;
            result[out_cnt++] = '=';
            if (out_cnt >= result_size)
                return result_size;
            result[out_cnt++] = '=';
        } else {
            if (out_cnt >= result_size)
                return result_size;
            result[out_cnt++] = base64_code[(bits >> 6) & 0x3f];
            if (out_cnt >= result_size)
                return result_size;
            result[out_cnt++] = '=';
        }
    }
    return (out_cnt >= result_size?result_size:out_cnt);
}
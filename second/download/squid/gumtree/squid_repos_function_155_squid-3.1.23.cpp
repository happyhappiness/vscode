void ska_base64_encode(char* result, const char *data, int result_size, int data_size)
{
    int bits = 0;
    int char_count = 0;
    int out_cnt = 0;

    if (!data)
        return;

    if (!base64_initialized)
        ska_base64_init();

    while (data_size--) {
        int c = (unsigned char) *data++;
        bits += c;
        char_count++;
        if (char_count == 3) {
            if (out_cnt >= result_size)
                break;
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
            bits = 0;
            char_count = 0;
        } else {
            bits <<= 8;
        }
    }
    if (char_count != 0) {
        bits <<= 16 - (8 * char_count);
        if (out_cnt >= result_size)
            goto end;
        result[out_cnt++] = base64_code[bits >> 18];
        if (out_cnt >= result_size)
            goto end;
        result[out_cnt++] = base64_code[(bits >> 12) & 0x3f];
        if (char_count == 1) {
            if (out_cnt >= result_size)
                goto end;
            result[out_cnt++] = '=';
            if (out_cnt >= result_size)
                goto end;
            result[out_cnt++] = '=';
        } else {
            if (out_cnt >= result_size)
                goto end;
            result[out_cnt++] = base64_code[(bits >> 6) & 0x3f];
            if (out_cnt >= result_size)
                goto end;
            result[out_cnt++] = '=';
        }
    }
end:
    if (out_cnt >= result_size) {
        result[result_size-1] = '\0';	/* terminate */
    } else {
        result[out_cnt] = '\0';	/* terminate */
    }
    return;
}
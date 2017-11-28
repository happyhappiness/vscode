const char *
base64_encode_bin(const char *decoded_str, int len)
{
    static char result[BASE64_RESULT_SZ];
    base64_encode_str(result, sizeof(result), decoded_str, len);
    return result;
}
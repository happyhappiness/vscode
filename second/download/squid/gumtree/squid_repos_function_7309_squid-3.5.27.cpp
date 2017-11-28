const char *
old_base64_encode(const char *decoded_str)
{
    static char result[BASE64_RESULT_SZ];
    base64_encode_str(result, sizeof(result), decoded_str, strlen(decoded_str));
    return result;
}
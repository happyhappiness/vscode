int
base64_encode_str(char *result, int result_max_size, const char *data, int data_size)
{
    if (result_max_size < 1)
        return 0;

    int used = base64_encode(result, result_max_size, data, data_size);
    /* terminate */
    if (used >= result_max_size) {
        result[result_max_size - 1] = '\0';
        return result_max_size;
    } else {
        result[used++] = '\0';
    }
    return used;
}
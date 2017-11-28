int
base64_decode_len(const char *data)
{
    if (!data || !*data)
        return 0;

    int terminatorLen = 0;
    int dataLen = strlen(data);
    int i;

    for (i = dataLen - 1; i >= 0; i--) {
        if (data[i] == '=')
            terminatorLen++;
        if (data[i] != '=')
            break;
    }
    return dataLen / 4 * 3 - terminatorLen;
}
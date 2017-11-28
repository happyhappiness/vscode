int ska_base64_decode_len(const char *data)
{
    int i,j;

    j=0;
    for (i=strlen(data)-1; i>=0; i--) {
        if (data[i] == '=') j++;
        if (data[i] != '=') break;
    }
    return strlen(data)/4*3-j;
}
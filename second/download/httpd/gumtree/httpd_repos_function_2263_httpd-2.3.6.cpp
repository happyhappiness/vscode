static int identity_concat(char *buffer, const char *key, const char *val)
{
    char *slider = buffer;
    int length = strlen(slider);
    slider += length;
    if (length) {
        *slider = '&';
        slider++;
    }
    ap_escape_path_segment_buffer(slider, key);
    slider += strlen(slider);
    *slider = '=';
    slider++;
    ap_escape_path_segment_buffer(slider, val);
    return 1;
}
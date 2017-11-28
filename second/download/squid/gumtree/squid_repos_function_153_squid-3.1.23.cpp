static void
ska_base64_init(void)
{
    int i;

    for (i = 0; i < BASE64_VALUE_SZ; i++)
        base64_value[i] = -1;

    for (i = 0; i < 64; i++)
        base64_value[(int) base64_code[i]] = i;
    base64_value['='] = 0;

    base64_initialized = 1;
}
 * encoding */
static int json_cfg_encode_max_depth(lua_State *l)
{
    json_config_t *cfg = json_arg_init(l, 1);

    return json_integer_option(l, 1, &cfg->encode_max_depth, 1, INT_MAX);
}

/* Configures the maximum number of nested arrays/objects allowed when
 * encoding */
static int json_cfg_decode_max_depth(lua_State *l)
{
    json_config_t *cfg = json_arg_init(l, 1);

    return json_integer_option(l, 1, &cfg->decode_max_depth, 1, INT_MAX);
}

/* Configures number precision when converting doubles to text */
static int json_cfg_encode_number_precision(lua_State *l)
{
    json_config_t *cfg = json_arg_init(l, 1);

    return json_integer_option(l, 1, &cfg->encode_number_precision, 1, 14);
}

/* Configures JSON encoding buffer persistence */
static int json_cfg_encode_keep_buffer(lua_State *l)
{
    json_config_t *cfg = json_arg_init(l, 1);
    int old_value;

    old_value = cfg->encode_keep_buffer;

    json_enum_option(l, 1, &cfg->encode_keep_buffer, NULL, 1);

    /* Init / free the buffer if the setting has changed */
    if (old_value ^ cfg->encode_keep_buffer) {
        if (cfg->encode_keep_buffer)
            strbuf_init(&cfg->encode_buf, 0);
        else
            strbuf_free(&cfg->encode_buf);
    }

    return 1;
}

#if defined(DISABLE_INVALID_NUMBERS) && !defined(USE_INTERNAL_FPCONV)
void json_verify_invalid_number_setting(lua_State *l, int *setting)
{
    if (*setting == 1) {
        *setting = 0;
        luaL_error(l, "Infinity, NaN, and/or hexadecimal numbers are not supported.");
    }
}
#else
#define json_verify_invalid_number_setting(l, s)    do { } while(0)
#endif

static int json_cfg_encode_invalid_numbers(lua_State *l)
{
    static const char *options[] = { "off", "on", "null", NULL };
    json_config_t *cfg = json_arg_init(l, 1);

    json_enum_option(l, 1, &cfg->encode_invalid_numbers, options, 1);

    json_verify_invalid_number_setting(l, &cfg->encode_invalid_numbers);

    return 1;
}

static int json_cfg_decode_invalid_numbers(lua_State *l)
{
    json_config_t *cfg = json_arg_init(l, 1);

    json_enum_option(l, 1, &cfg->decode_invalid_numbers, NULL, 1);

    json_verify_invalid_number_setting(l, &cfg->encode_invalid_numbers);

    return 1;
}

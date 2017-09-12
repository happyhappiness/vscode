static void json_append_number(lua_State *l, strbuf_t *json, int index,
                               json_config_t *cfg)
{
    double num = lua_tonumber(l, index);

    if (cfg->encode_refuse_badnum && (isinf(num) || isnan(num)))
        json_encode_exception(l, cfg, index, "must not be NaN or Inf");

    /* Lowest double printed with %.14g is 21 characters long:
     * -1.7976931348623e+308
     *
     * Use 32 to include the \0, and a few extra just in case..
     */
    strbuf_append_fmt(json, 32, cfg->number_fmt, num);
}
        break;;
    default:
        json_throw_parse_error(l, json, "value", token);
    }
}

/* json_text must be null terminated string */
static void lua_json_decode(lua_State *l, const char *json_text, int json_len)
{
    json_parse_t json;
    json_token_t token;

    json.cfg = json_fetch_config(l);
    json.data = json_text;
    json.index = 0;

    /* Ensure the temporary buffer can hold the entire string.
     * This means we no longer need to do length checks since the decoded
     * string must be smaller than the entire json string */
    json.tmp = strbuf_new(json_len);


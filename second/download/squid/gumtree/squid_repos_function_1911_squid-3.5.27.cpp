void
parse_header_token(external_acl_format::Pointer format, char *header, const Format::ByteCode_t type)
{
    /* header format */
    char *member, *end;

    /** Cut away the closing brace */
    end = strchr(header, '}');
    if (end && strlen(end) == 1)
        *end = '\0';
    else
        self_destruct();

    member = strchr(header, ':');

    if (member) {
        /* Split in header and member */
        *member = '\0';
        ++member;

        if (!xisalnum(*member)) {
            format->separator = *member;
            ++member;
        } else {
            format->separator = ',';
        }

        format->member = xstrdup(member);

        if (type == Format::LFT_ADAPTED_REQUEST_HEADER)
            format->type = Format::LFT_ADAPTED_REQUEST_HEADER_ELEM;
        else
            format->type = Format::LFT_REPLY_HEADER_ELEM;

    } else {
        format->type = type;
    }

    format->header = xstrdup(header);
    format->header_id = httpHeaderIdByNameDef(header, strlen(header));
}
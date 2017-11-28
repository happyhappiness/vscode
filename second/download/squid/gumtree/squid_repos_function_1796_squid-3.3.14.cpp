void
parse_header_token(external_acl_format *format, char *header, const _external_acl_format::format_type type)
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

        if (type == _external_acl_format::EXT_ACL_HEADER_REQUEST)
            format->type = _external_acl_format::EXT_ACL_HEADER_REQUEST_MEMBER;
        else
            format->type = _external_acl_format::EXT_ACL_HEADER_REQUEST_MEMBER;
    } else {
        format->type = type;
    }

    format->header = xstrdup(header);
    format->header_id = httpHeaderIdByNameDef(header, strlen(header));

    if (format->header_id != -1) {
        if (member) {
            if (type == _external_acl_format::EXT_ACL_HEADER_REQUEST)
                format->type = _external_acl_format::EXT_ACL_HEADER_REQUEST_ID_MEMBER;
            else
                format->type = _external_acl_format::EXT_ACL_HEADER_REPLY_ID_MEMBER;
        } else {
            if (type == _external_acl_format::EXT_ACL_HEADER_REQUEST)
                format->type = _external_acl_format::EXT_ACL_HEADER_REQUEST_ID;
            else
                format->type = _external_acl_format::EXT_ACL_HEADER_REPLY_ID;
        }
    }
}
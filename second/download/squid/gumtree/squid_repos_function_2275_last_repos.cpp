String
HttpHeader::getListMember(Http::HdrType id, const char *member, const char separator) const
{
    String header;
    const char *pos = NULL;
    const char *item;
    int ilen;
    int mlen = strlen(member);

    assert(any_registered_header(id));

    header = getStrOrList(id);
    String result;

    while (strListGetItem(&header, separator, &item, &ilen, &pos)) {
        if (strncmp(item, member, mlen) == 0 && item[mlen] == '=') {
            result.append(item + mlen + 1, ilen - mlen - 1);
            break;
        }
    }

    header.clean();
    return result;
}
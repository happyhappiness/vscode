bool
Ssl::ErrorDetailFile::parse(const char *buffer, int len, bool eof)
{
    if (!theDetails)
        return false;

    if (len) {
        buf.append(buffer, len);
    }

    if (eof)
        buf.append("\n\n", 1);

    while (size_t size = detailEntryEnd(buf.content(), buf.contentSize())) {
        const char *e = buf.content() + size;

        //ignore spaces, new lines and comment lines (starting with #) at the beggining
        const char *s;
        for (s = buf.content(); (*s == '\n' || *s == ' '  || *s == '\t' || *s == '#')  && s < e; ++s) {
            if (*s == '#')
                while (s<e &&  *s != '\n')
                    ++s; // skip untill the end of line
        }

        if ( s != e) {
            DetailEntryParser parser;
            if (!parser.parse(s, e - s)) {
                debugs(83, DBG_IMPORTANT, HERE <<
                       "WARNING! parse error on:" << s);
                return false;
            }

            const String errorName = parser.getByName("name");
            if (!errorName.size()) {
                debugs(83, DBG_IMPORTANT, HERE <<
                       "WARNING! invalid or no error detail name on:" << s);
                return false;
            }

            Security::ErrorCode ssl_error = Ssl::GetErrorCode(errorName.termedBuf());
            if (ssl_error != SSL_ERROR_NONE) {

                if (theDetails->getErrorDetail(ssl_error)) {
                    debugs(83, DBG_IMPORTANT, HERE <<
                           "WARNING! duplicate entry: " << errorName);
                    return false;
                }

                ErrorDetailEntry &entry = theDetails->theList[ssl_error];
                entry.error_no = ssl_error;
                entry.name = errorName;
                String tmp = parser.getByName("detail");
                const int detailsParseOk = httpHeaderParseQuotedString(tmp.termedBuf(), tmp.size(), &entry.detail);
                tmp = parser.getByName("descr");
                const int descrParseOk = httpHeaderParseQuotedString(tmp.termedBuf(), tmp.size(), &entry.descr);

                if (!detailsParseOk || !descrParseOk) {
                    debugs(83, DBG_IMPORTANT, HERE <<
                           "WARNING! missing important field for detail error: " <<  errorName);
                    return false;
                }

            } else if (!Ssl::ErrorIsOptional(errorName.termedBuf())) {
                debugs(83, DBG_IMPORTANT, HERE <<
                       "WARNING! invalid error detail name: " << errorName);
                return false;
            }

        }// else {only spaces and black lines; just ignore}

        buf.consume(size);
    }
    debugs(83, 9, HERE << " Remain size: " << buf.contentSize() << " Content: " << buf.content());
    return true;
}
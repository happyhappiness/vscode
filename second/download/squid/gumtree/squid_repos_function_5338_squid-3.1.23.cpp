void
ESIContext::parserComment (const char *s)
{
    if (failed())
        return;

    if (!strncmp(s, "esi",3)) {
        debugs(86, 5, "ESIContext::parserComment: ESI <!-- block encountered");
        ESIParser::Pointer tempParser = ESIParser::NewParser (this);

        /* wrap the comment in some tags */

        if (!tempParser->parse("<div>", 5,0) ||
                !tempParser->parse(s + 3, strlen(s) - 3, 0) ||
                !tempParser->parse("</div>",6,1)) {
            debugs(86, 0, "ESIContext::parserComment: Parsing fragment '" << s + 3 << "' failed.");
            setError();
            char tempstr[1024];
            snprintf(tempstr, 1023, "ESIContext::parserComment: Parse error at line %ld:\n%s\n",
                     tempParser->lineNumber(),
                     tempParser->errorString());
            debugs(86, 0, "" << tempstr << "");

            setErrorMessage(tempstr);
        }

        debugs(86, 5, "ESIContext::parserComment: ESI <!-- block parsed");
        return;
    } else {
        char localbuf [HTTP_REQBUF_SZ];
        unsigned int len;
        debugs(86, 5, "ESIContext::parserComment: Regenerating comment block");
        len = strlen (s);

        if (len > sizeof (localbuf) - 9) {
            debugs(86, 0, "ESIContext::parserComment: Truncating long comment");
            len = sizeof (localbuf) - 9;
        }

        xstrncpy(localbuf, "<!--", 5);
        xstrncpy(localbuf + 4, s, len + 1);
        xstrncpy(localbuf + 4 + len, "-->", 4);
        addLiteral (localbuf,len + 7);
    }
}
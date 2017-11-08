static const char* set_default(cmd_parms* cmd, void* CFG, const char* charset)
{
    xml2cfg* cfg = CFG;
    cfg->default_charset = charset;
    cfg->default_encoding = xmlParseCharEncoding(charset);
    switch(cfg->default_encoding) {
    case XML_CHAR_ENCODING_NONE:
        return "Default charset not found";
    case XML_CHAR_ENCODING_ERROR:
        return "Invalid or unsupported default charset";
    default:
        return NULL;
    }
}
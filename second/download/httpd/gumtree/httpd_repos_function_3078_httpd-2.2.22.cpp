static apr_status_t cleanup_parser(void *ctx)
{
    apr_xml_parser *parser = ctx;

    XML_ParserFree(parser->xp);
    parser->xp = NULL;

    return APR_SUCCESS;
}
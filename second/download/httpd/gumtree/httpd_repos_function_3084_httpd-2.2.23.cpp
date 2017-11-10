static apr_status_t do_parse(apr_xml_parser *parser,
                             const char *data, apr_size_t len,
                             int is_final)
{
    if (parser->xp == NULL) {
        parser->error = APR_XML_ERROR_PARSE_DONE;
    }
    else {
        int rv = XML_Parse(parser->xp, data, (int)len, is_final);

        if (rv == 0) {
            parser->error = APR_XML_ERROR_EXPAT;
            parser->xp_err = XML_GetErrorCode(parser->xp);
        }
    }

    /* ### better error code? */
    return parser->error ? APR_EGENERAL : APR_SUCCESS;
}
static void entity_declaration(void *userData, const XML_Char *entityName,
                               int is_parameter_entity, const XML_Char *value,
                               int value_length, const XML_Char *base,
                               const XML_Char *systemId, const XML_Char *publicId,
                               const XML_Char *notationName)
{
    apr_xml_parser *parser = userData;

    XML_StopParser(parser->xp, XML_FALSE);
}
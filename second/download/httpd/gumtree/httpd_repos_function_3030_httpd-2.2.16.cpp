static void end_handler(void *userdata, const char *name)
{
    apr_xml_parser *parser = userdata;

    /* punt once we find an error */
    if (parser->error)
	return;

    /* pop up one level */
    parser->cur_elem = parser->cur_elem->parent;
}
static void cdata_handler(void *userdata, const char *data, int len)
{
    apr_xml_parser *parser = userdata;
    apr_xml_elem *elem;
    apr_text_header *hdr;
    const char *s;

    /* punt once we find an error */
    if (parser->error)
	return;

    elem = parser->cur_elem;
    s = apr_pstrndup(parser->p, data, len);

    if (elem->last_child == NULL) {
	/* no children yet. this cdata follows the start tag */
	hdr = &elem->first_cdata;
    }
    else {
	/* child elements exist. this cdata follows the last child. */
	hdr = &elem->last_child->following_cdata;
    }

    apr_text_append(parser->p, hdr, s);
}
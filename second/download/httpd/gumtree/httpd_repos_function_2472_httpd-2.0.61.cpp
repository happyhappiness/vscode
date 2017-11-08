static char *write_elem(char *s, const apr_xml_elem *elem, int style,
			apr_array_header_t *namespaces, int *ns_map)
{
    const apr_xml_elem *child;
    apr_size_t len;
    int ns;

    if (style == APR_XML_X2T_FULL || style == APR_XML_X2T_FULL_NS_LANG) {
	int empty = APR_XML_ELEM_IS_EMPTY(elem);
	const apr_xml_attr *attr;

	if (elem->ns == APR_XML_NS_NONE) {
	    len = sprintf(s, "<%s", elem->name);
	}
	else {
	    ns = ns_map ? ns_map[elem->ns] : elem->ns;
	    len = sprintf(s, "<ns%d:%s", ns, elem->name);
	}
	s += len;

	for (attr = elem->attr; attr; attr = attr->next) {
	    if (attr->ns == APR_XML_NS_NONE)
		len = sprintf(s, " %s=\"%s\"", attr->name, attr->value);
            else {
                ns = ns_map ? ns_map[attr->ns] : attr->ns;
                len = sprintf(s, " ns%d:%s=\"%s\"", ns, attr->name, attr->value);
            }
	    s += len;
	}

	/* add the xml:lang value if necessary */
	if (elem->lang != NULL &&
	    (style == APR_XML_X2T_FULL_NS_LANG ||
	     elem->parent == NULL ||
	     elem->lang != elem->parent->lang)) {
	    len = sprintf(s, " xml:lang=\"%s\"", elem->lang);
	    s += len;
	}

	/* add namespace definitions, if required */
	if (style == APR_XML_X2T_FULL_NS_LANG) {
	    int i;

	    for (i = namespaces->nelts; i--;) {
		len = sprintf(s, " xmlns:ns%d=\"%s\"", i,
			      APR_XML_GET_URI_ITEM(namespaces, i));
		s += len;
	    }
	}

	/* no more to do. close it up and go. */
	if (empty) {
	    *s++ = '/';
	    *s++ = '>';
	    return s;
	}

	/* just close it */
	*s++ = '>';
    }
    else if (style == APR_XML_X2T_LANG_INNER) {
	/* prepend the xml:lang value */
	if (elem->lang != NULL) {
	    len = strlen(elem->lang);
	    memcpy(s, elem->lang, len);
	    s += len;
	}
	*s++ = '\0';
    }

    s = write_text(s, elem->first_cdata.first);

    for (child = elem->first_child; child; child = child->next) {
	s = write_elem(s, child, APR_XML_X2T_FULL, NULL, ns_map);
	s = write_text(s, child->following_cdata.first);
    }

    if (style == APR_XML_X2T_FULL || style == APR_XML_X2T_FULL_NS_LANG) {
	if (elem->ns == APR_XML_NS_NONE) {
	    len = sprintf(s, "</%s>", elem->name);
	}
	else {
	    ns = ns_map ? ns_map[elem->ns] : elem->ns;
	    len = sprintf(s, "</ns%d:%s>", ns, elem->name);
	}
	s += len;
    }

    return s;
}
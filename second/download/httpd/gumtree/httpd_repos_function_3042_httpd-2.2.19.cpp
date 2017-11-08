static apr_size_t elem_size(const apr_xml_elem *elem, int style,
                            apr_array_header_t *namespaces, int *ns_map)
{
    apr_size_t size;

    if (style == APR_XML_X2T_FULL || style == APR_XML_X2T_FULL_NS_LANG) {
	const apr_xml_attr *attr;

	size = 0;

	if (style == APR_XML_X2T_FULL_NS_LANG) {
	    int i;

	    /*
	    ** The outer element will contain xmlns:ns%d="%s" attributes
	    ** and an xml:lang attribute, if applicable.
	    */

	    for (i = namespaces->nelts; i--;) {
		/* compute size of: ' xmlns:ns%d="%s"' */
		size += (9 + APR_XML_NS_LEN(i) + 2 +
			 strlen(APR_XML_GET_URI_ITEM(namespaces, i)) + 1);
	    }

	    if (elem->lang != NULL) {
		/* compute size of: ' xml:lang="%s"' */
		size += 11 + strlen(elem->lang) + 1;
	    }
	}

	if (elem->ns == APR_XML_NS_NONE) {
	    /* compute size of: <%s> */
	    size += 1 + strlen(elem->name) + 1;
	}
	else {
	    int ns = ns_map ? ns_map[elem->ns] : elem->ns;

	    /* compute size of: <ns%d:%s> */
	    size += 3 + APR_XML_NS_LEN(ns) + 1 + strlen(elem->name) + 1;
	}

	if (APR_XML_ELEM_IS_EMPTY(elem)) {
	    /* insert a closing "/" */
	    size += 1;
	}
	else {
	    /*
	     * two of above plus "/":
	     *     <ns%d:%s> ... </ns%d:%s>
	     * OR  <%s> ... </%s>
	     */
	    size = 2 * size + 1;
	}

	for (attr = elem->attr; attr; attr = attr->next) {
	    if (attr->ns == APR_XML_NS_NONE) {
		/* compute size of: ' %s="%s"' */
		size += 1 + strlen(attr->name) + 2 + strlen(attr->value) + 1;
	    }
	    else {
		/* compute size of: ' ns%d:%s="%s"' */
                int ns = ns_map ? ns_map[attr->ns] : attr->ns;
                size += 3 + APR_XML_NS_LEN(ns) + 1 + strlen(attr->name) + 2 + strlen(attr->value) + 1;
	    }
	}

	/*
	** If the element has an xml:lang value that is *different* from
	** its parent, then add the thing in: ' xml:lang="%s"'.
	**
	** NOTE: we take advantage of the pointer equality established by
	** the parsing for "inheriting" the xml:lang values from parents.
	*/
	if (elem->lang != NULL &&
	    (elem->parent == NULL || elem->lang != elem->parent->lang)) {
	    size += 11 + strlen(elem->lang) + 1;
	}
    }
    else if (style == APR_XML_X2T_LANG_INNER) {
	/*
	 * This style prepends the xml:lang value plus a null terminator.
	 * If a lang value is not present, then we insert a null term.
	 */
	size = elem->lang ? strlen(elem->lang) + 1 : 1;
    }
    else
	size = 0;

    size += text_size(elem->first_cdata.first);

    for (elem = elem->first_child; elem; elem = elem->next) {
	/* the size of the child element plus the CDATA that follows it */
	size += (elem_size(elem, APR_XML_X2T_FULL, NULL, ns_map) +
		 text_size(elem->following_cdata.first));
    }

    return size;
}
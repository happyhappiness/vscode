static void start_handler(void *userdata, const char *name, const char **attrs)
{
    apr_xml_parser *parser = userdata;
    apr_xml_elem *elem;
    apr_xml_attr *attr;
    apr_xml_attr *prev;
    char *colon;
    const char *quoted;
    char *elem_name;

    /* punt once we find an error */
    if (parser->error)
	return;

    elem = apr_pcalloc(parser->p, sizeof(*elem));

    /* prep the element */
    elem->name = elem_name = apr_pstrdup(parser->p, name);

    /* fill in the attributes (note: ends up in reverse order) */
    while (*attrs) {
	attr = apr_palloc(parser->p, sizeof(*attr));
	attr->name = apr_pstrdup(parser->p, *attrs++);
	attr->value = apr_pstrdup(parser->p, *attrs++);
	attr->next = elem->attr;
	elem->attr = attr;
    }

    /* hook the element into the tree */
    if (parser->cur_elem == NULL) {
	/* no current element; this also becomes the root */
	parser->cur_elem = parser->doc->root = elem;
    }
    else {
	/* this element appeared within the current elem */
	elem->parent = parser->cur_elem;

	/* set up the child/sibling links */
	if (elem->parent->last_child == NULL) {
	    /* no first child either */
	    elem->parent->first_child = elem->parent->last_child = elem;
	}
	else {
	    /* hook onto the end of the parent's children */
	    elem->parent->last_child->next = elem;
	    elem->parent->last_child = elem;
	}

	/* this element is now the current element */
	parser->cur_elem = elem;
    }

    /* scan the attributes for namespace declarations */
    for (prev = NULL, attr = elem->attr;
	 attr;
	 attr = attr->next) {
	if (strncmp(attr->name, "xmlns", 5) == 0) {
	    const char *prefix = &attr->name[5];
	    apr_xml_ns_scope *ns_scope;

	    /* test for xmlns:foo= form and xmlns= form */
	    if (*prefix == ':') {
                /* a namespace prefix declaration must have a
                   non-empty value. */
                if (attr->value[0] == '\0') {
                    parser->error = APR_XML_NS_ERROR_INVALID_DECL;
                    return;
                }
		++prefix;
            }
	    else if (*prefix != '\0') {
		/* advance "prev" since "attr" is still present */
		prev = attr;
		continue;
	    }

	    /* quote the URI before we ever start working with it */
	    quoted = apr_xml_quote_string(parser->p, attr->value, 1);

	    /* build and insert the new scope */
	    ns_scope = apr_pcalloc(parser->p, sizeof(*ns_scope));
	    ns_scope->prefix = prefix;
	    ns_scope->ns = apr_xml_insert_uri(parser->doc->namespaces, quoted);
	    ns_scope->emptyURI = *quoted == '\0';
	    ns_scope->next = elem->ns_scope;
	    elem->ns_scope = ns_scope;

	    /* remove this attribute from the element */
	    if (prev == NULL)
		elem->attr = attr->next;
	    else
		prev->next = attr->next;

	    /* Note: prev will not be advanced since we just removed "attr" */
	}
	else if (strcmp(attr->name, "xml:lang") == 0) {
	    /* save away the language (in quoted form) */
	    elem->lang = apr_xml_quote_string(parser->p, attr->value, 1);

	    /* remove this attribute from the element */
	    if (prev == NULL)
		elem->attr = attr->next;
	    else
		prev->next = attr->next;

	    /* Note: prev will not be advanced since we just removed "attr" */
	}
	else {
	    /* advance "prev" since "attr" is still present */
	    prev = attr;
	}
    }

    /*
    ** If an xml:lang attribute didn't exist (lang==NULL), then copy the
    ** language from the parent element (if present).
    **
    ** NOTE: elem_size() *depends* upon this pointer equality.
    */
    if (elem->lang == NULL && elem->parent != NULL)
	elem->lang = elem->parent->lang;

    /* adjust the element's namespace */
    colon = strchr(elem_name, ':');
    if (colon == NULL) {
	/*
	 * The element is using the default namespace, which will always
	 * be found. Either it will be "no namespace", or a default
	 * namespace URI has been specified at some point.
	 */
	elem->ns = find_prefix(parser, "");
    }
    else if (APR_XML_NS_IS_RESERVED(elem->name)) {
	elem->ns = APR_XML_NS_NONE;
    }
    else {
	*colon = '\0';
	elem->ns = find_prefix(parser, elem->name);
	elem->name = colon + 1;

	if (APR_XML_NS_IS_ERROR(elem->ns)) {
	    parser->error = elem->ns;
	    return;
	}
    }

    /* adjust all remaining attributes' namespaces */
    for (attr = elem->attr; attr; attr = attr->next) {
        /*
         * apr_xml_attr defines this as "const" but we dup'd it, so we
         * know that we can change it. a bit hacky, but the existing
         * structure def is best.
         */
        char *attr_name = (char *)attr->name;

	colon = strchr(attr_name, ':');
	if (colon == NULL) {
	    /*
	     * Attributes do NOT use the default namespace. Therefore,
	     * we place them into the "no namespace" category.
	     */
	    attr->ns = APR_XML_NS_NONE;
	}
	else if (APR_XML_NS_IS_RESERVED(attr->name)) {
	    attr->ns = APR_XML_NS_NONE;
	}
	else {
	    *colon = '\0';
	    attr->ns = find_prefix(parser, attr->name);
	    attr->name = colon + 1;

	    if (APR_XML_NS_IS_ERROR(attr->ns)) {
		parser->error = attr->ns;
		return;
	    }
	}
    }
}
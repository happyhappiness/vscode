apr_xml_elem *dav_find_child(const apr_xml_elem *elem, const char *tagname)
{
    apr_xml_elem *child = elem->first_child;

    for (; child; child = child->next)
        if (child->ns == APR_XML_NS_DAV_ID && !strcmp(child->name, tagname))
            return child;
    return NULL;
}
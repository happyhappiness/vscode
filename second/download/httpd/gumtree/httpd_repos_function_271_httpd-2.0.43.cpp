int dav_validate_root(const apr_xml_doc *doc, const char *tagname)
{
    return doc->root &&
	doc->root->ns == APR_XML_NS_DAV_ID &&
	strcmp(doc->root->name, tagname) == 0;
}
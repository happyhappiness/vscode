static std::string
build_searchbase(const char *extension_dn, const char *base_dn)
{
    std::stringstream searchBaseStream;
    if (extension_dn && *extension_dn)
        searchBaseStream << extension_dn << ",";
    searchBaseStream << base_dn;
    return searchBaseStream.str();
}
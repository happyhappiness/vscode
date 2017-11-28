void
ACLCertificateData::parse()
{
    if (validAttributesStr) {
        char *newAttribute = ConfigParser::strtokFile();

        if (!newAttribute) {
            if (!attributeIsOptional) {
                debugs(28, DBG_CRITICAL, "FATAL: required attribute argument missing");
                self_destruct();
            }
            return;
        }

        // Handle the cases where we have optional -x type attributes
        if (attributeIsOptional && newAttribute[0] != '-')
            // The read token is not an attribute/option, so add it to values list
            values.insert(newAttribute);
        else {
            bool valid = false;
            for (std::list<std::string>::const_iterator it = validAttributes.begin(); it != validAttributes.end(); ++it) {
                if (*it == "*" || *it == newAttribute) {
                    valid = true;
                    break;
                }
            }

            if (!valid) {
                debugs(28, DBG_CRITICAL, "FATAL: Unknown option. Supported option(s) are: " << validAttributesStr);
                self_destruct();
                return;
            }

            /* an acl must use consistent attributes in all config lines */
            if (attribute) {
                if (strcasecmp(newAttribute, attribute) != 0) {
                    debugs(28, DBG_CRITICAL, "FATAL: An acl must use consistent attributes in all config lines (" << newAttribute << "!=" << attribute << ").");
                    self_destruct();
                    return;
                }
            } else {
                if (strcasecmp(newAttribute, "DN") != 0) {
                    int nid = OBJ_txt2nid(newAttribute);
                    if (nid == 0) {
                        const size_t span = strspn(newAttribute, "0123456789.");
                        if(newAttribute[span] == '\0') { // looks like a numerical OID
                            // create a new object based on this attribute

                            // NOTE: Not a [bad] leak: If the same attribute
                            // has been added before, the OBJ_txt2nid call
                            // would return a valid nid value.
                            // TODO: call OBJ_cleanup() on reconfigure?
                            nid = OBJ_create(newAttribute, newAttribute,  newAttribute);
                            debugs(28, 7, "New SSL certificate attribute created with name: " << newAttribute << " and nid: " << nid);
                        }
                    }
                    if (nid == 0) {
                        debugs(28, DBG_CRITICAL, "FATAL: Not valid SSL certificate attribute name or numerical OID: " << newAttribute);
                        self_destruct();
                        return;
                    }
                }
                attribute = xstrdup(newAttribute);
            }
        }
    }

    values.parse();
}
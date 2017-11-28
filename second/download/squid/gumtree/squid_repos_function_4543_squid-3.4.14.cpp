void
ACLCertificateData::parse()
{
    if (validAttributesStr) {
        char *newAttribute = strtokFile();

        if (!newAttribute) {
            if (attributeIsOptional)
                return;

            debugs(28, DBG_CRITICAL, "FATAL: required attribute argument missing");
            self_destruct();
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
            }

            /* an acl must use consistent attributes in all config lines */
            if (attribute) {
                if (strcasecmp(newAttribute, attribute) != 0) {
                    debugs(28, DBG_CRITICAL, "FATAL: An acl must use consistent attributes in all config lines (" << newAttribute << "!=" << attribute << ").");
                    self_destruct();
                }
            } else
                attribute = xstrdup(newAttribute);
        }
    }

    values.parse();
}
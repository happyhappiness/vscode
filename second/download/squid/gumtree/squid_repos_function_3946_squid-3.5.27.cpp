bool
Adaptation::ServiceConfig::parse()
{
    key = ConfigParser::NextToken();
    String method_point = ConfigParser::NextToken();
    if (!method_point.size()) {
        debugs(3, DBG_CRITICAL, "ERROR: " << cfg_filename << ':' << config_lineno << ": " <<
               "Missing vectoring point in adaptation service definition");
        return false;
    }

    method = parseMethod(method_point.termedBuf());
    point = parseVectPoint(method_point.termedBuf());
    if (method == Adaptation::methodNone && point == Adaptation::pointNone) {
        debugs(3, DBG_CRITICAL, "ERROR: " << cfg_filename << ':' << config_lineno << ": " <<
               "Unknown vectoring point '" << method_point << "' in adaptation service definition");
        return false;
    }

    // reset optional parameters in case we are reconfiguring
    bypass = routing = false;

    // handle optional service name=value parameters
    bool grokkedUri = false;
    bool onOverloadSet = false;
    std::set<std::string> options;

    while (char *option = ConfigParser::NextToken()) {
        const char *name = option;
        const char *value = "";
        if (strcmp(option, "0") == 0) { // backward compatibility
            name = "bypass";
            value = "off";
            debugs(3, DBG_PARSE_NOTE(DBG_IMPORTANT), "UPGRADE: Please use 'bypass=off' option to disable service bypass");
        }  else if (strcmp(option, "1") == 0) { // backward compatibility
            name = "bypass";
            value = "on";
            debugs(3, DBG_PARSE_NOTE(DBG_IMPORTANT), "UPGRADE: Please use 'bypass=on' option to enable service bypass");
        } else {
            char *eq = strstr(option, "=");
            const char *sffx = strstr(option, "://");
            if (!eq || (sffx && sffx < eq)) { //no "=" or has the form "icap://host?arg=val"
                name = "uri";
                value = option;
            }  else { // a normal name=value option
                *eq = '\0'; // terminate option name
                value = eq + 1; // skip '='
            }
        }

        // Check if option is set twice
        if (options.find(name) != options.end()) {
            debugs(3, DBG_CRITICAL, "ERROR: " << cfg_filename << ':' << config_lineno << ": " <<
                   "Duplicate option \"" << name << "\" in adaptation service definition");
            return false;
        }
        options.insert(name);

        bool grokked = false;
        if (strcmp(name, "bypass") == 0) {
            grokked = grokBool(bypass, name, value);
        } else if (strcmp(name, "routing") == 0)
            grokked = grokBool(routing, name, value);
        else if (strcmp(name, "uri") == 0)
            grokked = grokkedUri = grokUri(value);
        else if (strcmp(name, "ipv6") == 0) {
            grokked = grokBool(ipv6, name, value);
            if (grokked && ipv6 && !Ip::EnableIpv6)
                debugs(3, DBG_PARSE_NOTE(DBG_IMPORTANT), "WARNING: IPv6 is disabled. ICAP service option ignored.");
        } else if (strcmp(name, "max-conn") == 0)
            grokked = grokLong(maxConn, name, value);
        else if (strcmp(name, "on-overload") == 0) {
            grokked = grokOnOverload(onOverload, value);
            onOverloadSet = true;
        } else
            grokked = grokExtension(name, value);

        if (!grokked)
            return false;
    }

    // set default on-overload value if needed
    if (!onOverloadSet)
        onOverload = bypass ? srvBypass : srvWait;

    // is the service URI set?
    if (!grokkedUri) {
        debugs(3, DBG_CRITICAL, "ERROR: " << cfg_filename << ':' << config_lineno << ": " <<
               "No \"uri\" option in adaptation service definition");
        return false;
    }

    debugs(3,5, cfg_filename << ':' << config_lineno << ": " <<
           "adaptation_service " << key << ' ' <<
           methodStr() << "_" << vectPointStr() << ' ' <<
           bypass << routing << ' ' <<
           uri);

    return true;
}
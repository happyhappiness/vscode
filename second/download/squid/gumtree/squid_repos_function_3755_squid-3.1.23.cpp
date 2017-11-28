bool
Adaptation::ServiceConfig::parse()
{
    char *method_point = NULL;

    ConfigParser::ParseString(&key);
    ConfigParser::ParseString(&method_point);
    method = parseMethod(method_point);
    point = parseVectPoint(method_point);

    // reset optional parameters in case we are reconfiguring
    bypass = routing = false;

    // handle optional service name=value parameters
    const char *lastOption = NULL;
    while (char *option = strtok(NULL, w_space)) {
        if (strcmp(option, "0") == 0) { // backward compatibility
            bypass = false;
            continue;
        }
        if (strcmp(option, "1") == 0) { // backward compatibility
            bypass = true;
            continue;
        }

        const char *name = option;
        char *value = strstr(option, "=");
        if (!value) {
            lastOption = option;
            break;
        }
        *value = '\0'; // terminate option name
        ++value; // skip '='

        // TODO: warn if option is set twice?
        bool grokked = false;
        if (strcmp(name, "bypass") == 0)
            grokked = grokBool(bypass, name, value);
        else if (strcmp(name, "routing") == 0)
            grokked = grokBool(routing, name, value);
        else if (strcmp(name, "ipv6") == 0) {
            grokked = grokBool(ipv6, name, value);
            if (grokked && ipv6 && !Ip::EnableIpv6)
                debugs(3, DBG_IMPORTANT, "WARNING: IPv6 is disabled. ICAP service option ignored.");
        } else {
            debugs(3, 0, cfg_filename << ':' << config_lineno << ": " <<
                   "unknown adaptation service option: " << name << '=' << value);
        }
        if (!grokked)
            return false;
    }

    // what is left must be the service URI
    if (!grokUri(lastOption))
        return false;

    // there should be nothing else left
    if (const char *tail = strtok(NULL, w_space)) {
        debugs(3, 0, cfg_filename << ':' << config_lineno << ": " <<
               "garbage after adaptation service URI: " << tail);
        return false;
    }

    debugs(3,5, cfg_filename << ':' << config_lineno << ": " <<
           "adaptation_service " << key << ' ' <<
           methodStr() << "_" << vectPointStr() << ' ' <<
           bypass << routing << ' ' <<
           uri);

    return true;
}
static void
DisplayConf()
{
    if (!(edui_conf.mode & EDUI_MODE_DEBUG))
        return;
    DisplayVersion();
    local_printfx("\n");
    local_printfx("Configuration:\n");
    local_printfx("	EDUI_MAXLEN: %u\n", EDUI_MAXLEN);
    if (edui_conf.mode & EDUI_MODE_DEBUG)
        local_printfx("	Debug mode: ON\n");
    else
        local_printfx("	Debug mode: OFF\n");
    if (edui_conf.mode & EDUI_MODE_IPV4)
        local_printfx("	Address format: IPv4 (127.0.0.1)\n");
    else if (edui_conf.mode & EDUI_MODE_IPV6)
        local_printfx("	Address format: IPv6 (::1)\n");
    else
        local_printfx("	Address format: Not enforced.\n");
    if (edui_conf.host[0] != '\0')
        local_printfx("	Hostname: %s\n", edui_conf.host);
    else
        local_printfx("	Hostname: localhost\n");
    if (edui_conf.port > 0)
        local_printfx("	Port: %d\n", edui_conf.port);
    else
        local_printfx("	Port: %d\n", LDAP_PORT);
    if (edui_conf.mode & EDUI_MODE_TLS)
        local_printfx("	TLS mode: ON\n");
    else
        local_printfx("	TLS mode: OFF\n");
    if (edui_conf.mode & EDUI_MODE_PERSIST) {
        local_printfx("	Persistent mode: ON\n");
        if (edui_conf.persist_timeout > 0)
            local_printfx("	Persistent mode idle timeout: %d\n", edui_conf.persist_timeout);
        else
            local_printfx("	Persistent mode idle timeout: OFF\n");
    } else
        local_printfx("	Persistent mode: OFF\n");
    local_printfx("	LDAP Version: %d\n", edui_conf.ver);
    if (edui_conf.basedn[0] != '\0')
        local_printfx("	Base DN: %s\n", edui_conf.basedn);
    else
        local_printfx("	Base DN: None\n");
    if (edui_conf.dn[0] != '\0')
        local_printfx("	Binding DN: %s\n", edui_conf.dn);
    else
        local_printfx("	Binding DN: Anonymous\n");
    if (edui_conf.passwd[0] != '\0')
        local_printfx("	Binding Password: %s\n", edui_conf.passwd);
    else
        local_printfx("	Binding Password: None\n");
    switch (edui_conf.scope) {
    case 0:
        local_printfx("	Search Scope: base\n");
        break;
    case 1:
        local_printfx("	Search Scope: one level\n");
        break;
    case 2:
        local_printfx("	Search Scope: subtree\n");
        break;
    default:
        local_printfx("	Search Scope: base\n");
        break;
    }
    if (edui_conf.attrib[0] != '\0')
        local_printfx("	Search Attribute: %s\n", edui_conf.attrib);
    else
        local_printfx("	Search Attribute: cn\n");
    if (edui_conf.search_filter[0] != '\0')
        local_printfx("	Search Filter: %s\n", edui_conf.search_filter);
    else
        local_printfx("	Search Filter: (&(objectClass=User)(networkAddress=*))\n");
    if (edui_conf.mode & EDUI_MODE_GROUP)
        local_printfx("	Search Group Required: Yes\n");
    else
        local_printfx("	Search Group Required: No\n");
    local_printfx("\n");
}
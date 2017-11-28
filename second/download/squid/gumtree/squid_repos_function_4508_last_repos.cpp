void
Store::Disk::parseOptions(int isaReconfig)
{
    const bool old_read_only = flags.read_only;
    char *name, *value;

    ConfigOption *newOption = getOptionTree();

    while ((name = ConfigParser::NextToken()) != NULL) {
        value = strchr(name, '=');

        if (value) {
            *value = '\0';  /* cut on = */
            ++value;
        }

        debugs(3,2, "cache_dir " << name << '=' << (value ? value : ""));

        if (newOption)
            if (!newOption->parse(name, value, isaReconfig))
                self_destruct();
    }

    delete newOption;

    /*
     * Handle notifications about reconfigured single-options with no value
     * where the removal of the option cannot be easily detected in the
     * parsing...
     */

    if (isaReconfig) {
        if (old_read_only != flags.read_only) {
            debugs(3, DBG_IMPORTANT, "Cache dir '" << path << "' now " << (flags.read_only ? "No-Store" : "Read-Write"));
        }
    }
}
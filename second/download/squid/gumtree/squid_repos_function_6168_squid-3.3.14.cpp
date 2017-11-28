void
Format::FmtConfig::parseFormats()
{
    char *name, *def;

    if ((name = strtok(NULL, w_space)) == NULL)
        self_destruct();

    if ((def = strtok(NULL, "\r\n")) == NULL) {
        self_destruct();
        return;
    }

    debugs(3, 2, "Custom Format for '" << name << "' is '" << def << "'");

    Format *nlf = new Format(name);

    if (!nlf->parse(def)) {
        self_destruct();
        return;
    }

    // add to global config list
    nlf->next = formats;
    formats = nlf;
}
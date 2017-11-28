void
ConfigOptionVector::dump(StoreEntry * e) const
{
    for (Vector<ConfigOption *>::const_iterator i = options.begin();
            i != options.end(); ++i)
        (*i)->dump(e);
}
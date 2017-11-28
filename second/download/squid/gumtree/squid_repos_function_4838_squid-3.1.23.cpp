AuthScheme *
AuthScheme::Find(const char *typestr)
{
    for (iterator i = GetSchemes().begin(); i != GetSchemes().end(); ++i) {
        if (strcmp ((*i)->type(), typestr) == 0)
            return *i;
    }

    return NULL;
}
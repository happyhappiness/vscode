Auth::Scheme::Pointer
Auth::Scheme::Find(const char *typestr)
{
    for (iterator i = GetSchemes().begin(); i != GetSchemes().end(); ++i) {
        if (strcmp((*i)->type(), typestr) == 0)
            return *i;
    }

    return Auth::Scheme::Pointer(NULL);
}
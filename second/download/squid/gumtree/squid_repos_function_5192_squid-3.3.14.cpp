void
Auth::Scheme::AddScheme(Auth::Scheme::Pointer instance)
{
    iterator i = GetSchemes().begin();

    while (i != GetSchemes().end()) {
        assert(strcmp((*i)->type(), instance->type()) != 0);
        ++i;
    }

    GetSchemes().push_back(instance);
}
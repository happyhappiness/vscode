static void
free_names(usersfile * uf)
{
    int i;
    for (i = 0; i < uf->Inuse; ++i) {
        if (uf->names[i])
            free(uf->names[i]);
        uf->names[i] = NULL;
    }
    uf->Inuse = 0;
}
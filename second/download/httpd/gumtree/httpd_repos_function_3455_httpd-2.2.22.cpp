int DisposeLibraryData(void *data)
{
    if (data)
    {
        library_free(data);
    }

    return 0;
}
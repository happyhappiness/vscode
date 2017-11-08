void
closedirectory(directory_type *dir)
{
FindClose(dir->handle);
free(dir);
}
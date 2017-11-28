const char *
StoreEntry::url() const
{
    if (this == NULL)
        return "[null_entry]";
    else if (mem_obj == NULL)
        return "[null_mem_obj]";
    else
        return mem_obj->url;
}
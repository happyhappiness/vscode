String
Ipc::Mem::Segment::GenerateName(const char *id)
{
    assert(BasePath && *BasePath);
    static const bool nameIsPath = shm_portable_segment_name_is_path();
    String name;
    if (nameIsPath) {
        name.append(BasePath);
        if (name[name.size()-1] != '/')
            name.append('/');
    } else
        name.append("/squid-");

    // append id, replacing slashes with dots
    for (const char *slash = strchr(id, '/'); slash; slash = strchr(id, '/')) {
        if (id != slash) {
            name.append(id, slash - id);
            name.append('.');
        }
        id = slash + 1;
    }
    name.append(id);

    name.append(".shm"); // to distinguish from non-segments when nameIsPath
    return name;
}
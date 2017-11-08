const char *darwin_dynamic_link_function(const char *version_info)
{
    char *newarg;
    long major, minor, patch;

    major = 0;
    minor = 0;
    patch = 0;

    if (version_info) {
        major = safe_strtol(version_info, &version_info, 10);

        if (version_info) {
            if (version_info[0] == ':') {
                version_info++;
            }

            minor = safe_strtol(version_info, &version_info, 10);

            if (version_info) {
                if (version_info[0] == ':') {
                    version_info++;
                }

                patch = safe_strtol(version_info, &version_info, 10);

            }
        }
    }

    /* Avoid -dylib_compatibility_version must be greater than zero errors. */
    if (major == 0) {
        major = 1;
    }
    newarg = (char*)malloc(100);
    snprintf(newarg, 99,
             "-compatibility_version %ld -current_version %ld.%ld",
             major, major, minor);

    return newarg;
}
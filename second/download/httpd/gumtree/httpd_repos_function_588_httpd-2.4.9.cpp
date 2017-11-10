static int compare_version(char *version_string, const char **error)
{
    char *p = version_string, *ep;
    int version[3] = {0, 0, 0};
    int c = 0;

    *error = "Version appears to be invalid. It must have the format "
             "major[.minor[.patch]] where major, minor and patch are "
             "numbers.";

    if (!apr_isdigit(*p)) {
        return 0;
    }

    /* parse supplied version */
    ep = version_string + strlen(version_string);
    while (p <= ep && c < 3) {
        if (*p == '.') {
            *p = '\0';
        }

        if (!*p) {
            version[c++] = atoi(version_string);
            version_string = ++p;
            continue;
        }

        if (!apr_isdigit(*p)) {
            break;
        }

        ++p;
    }

    if (p < ep) { /* syntax error */
        return 0;
    }

    *error = NULL;

    if      (httpd_version.major > version[0]) {
        return 1;
    }
    else if (httpd_version.major < version[0]) {
        return -1;
    }
    else if (httpd_version.minor > version[1]) {
        return 1;
    }
    else if (httpd_version.minor < version[1]) {
        return -1;
    }
    else if (httpd_version.patch > version[2]) {
        return 1;
    }
    else if (httpd_version.patch < version[2]) {
        return -1;
    }

    /* seems to be the same */
    return 0;
}
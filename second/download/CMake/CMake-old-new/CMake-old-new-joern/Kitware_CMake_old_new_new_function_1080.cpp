static int
archive_write_pax_header(struct archive_write *a,
    struct archive_entry *entry_original)
{
    struct archive_entry *entry_main;
    const char *p;
    char *t;
    const wchar_t *wp;
    const char *suffix;
    int need_extension, r, ret;
    struct pax *pax;
    const char *hdrcharset = NULL;
    const char *hardlink;
    const char *path = NULL, *linkpath = NULL;
    const char *uname = NULL, *gname = NULL;
    const wchar_t *path_w = NULL, *linkpath_w = NULL;
    const wchar_t *uname_w = NULL, *gname_w = NULL;

    char paxbuff[512];
    char ustarbuff[512];
    char ustar_entry_name[256];
    char pax_entry_name[256];

    ret = ARCHIVE_OK;
    need_extension = 0;
    pax = (struct pax *)a->format_data;

    hardlink = archive_entry_hardlink(entry_original);

    /* Make sure this is a type of entry that we can handle here */
    if (hardlink == NULL) {
        switch (archive_entry_filetype(entry_original)) {
        case AE_IFBLK:
        case AE_IFCHR:
        case AE_IFIFO:
        case AE_IFLNK:
        case AE_IFREG:
            break;
        case AE_IFDIR:
            /*
             * Ensure a trailing '/'.  Modify the original
             * entry so the client sees the change.
             */
            p = archive_entry_pathname(entry_original);
            if (p[strlen(p) - 1] != '/') {
                t = (char *)malloc(strlen(p) + 2);
                if (t == NULL) {
                    archive_set_error(&a->archive, ENOMEM,
                    "Can't allocate pax data");
                    return(ARCHIVE_FATAL);
                }
                strcpy(t, p);
                strcat(t, "/");
                archive_entry_copy_pathname(entry_original, t);
                free(t);
            }
            break;
        case AE_IFSOCK:
            archive_set_error(&a->archive,
                ARCHIVE_ERRNO_FILE_FORMAT,
                "tar format cannot archive socket");
            return (ARCHIVE_WARN);
        default:
            archive_set_error(&a->archive,
                ARCHIVE_ERRNO_FILE_FORMAT,
                "tar format cannot archive this (type=0%lo)",
                (unsigned long)archive_entry_filetype(entry_original));
            return (ARCHIVE_WARN);
        }
    }

    /* Copy entry so we can modify it as needed. */
    entry_main = archive_entry_clone(entry_original);
    archive_string_empty(&(pax->pax_header)); /* Blank our work area. */

    /*
     * First, check the name fields and see if any of them
     * require binary coding.  If any of them does, then all of
     * them do.
     */
    hdrcharset = NULL;
    path = archive_entry_pathname(entry_main);
    path_w = archive_entry_pathname_w(entry_main);
    if (path != NULL && path_w == NULL) {
        archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
            "Can't translate pathname '%s' to UTF-8", path);
        ret = ARCHIVE_WARN;
        hdrcharset = "BINARY";
    }
    uname = archive_entry_uname(entry_main);
    uname_w = archive_entry_uname_w(entry_main);
    if (uname != NULL && uname_w == NULL) {
        archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
            "Can't translate uname '%s' to UTF-8", uname);
        ret = ARCHIVE_WARN;
        hdrcharset = "BINARY";
    }
    gname = archive_entry_gname(entry_main);
    gname_w = archive_entry_gname_w(entry_main);
    if (gname != NULL && gname_w == NULL) {
        archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
            "Can't translate gname '%s' to UTF-8", gname);
        ret = ARCHIVE_WARN;
        hdrcharset = "BINARY";
    }
    linkpath = hardlink;
    if (linkpath != NULL) {
        linkpath_w = archive_entry_hardlink_w(entry_main);
    } else {
        linkpath = archive_entry_symlink(entry_main);
        if (linkpath != NULL)
            linkpath_w = archive_entry_symlink_w(entry_main);
    }
    if (linkpath != NULL && linkpath_w == NULL) {
        archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
            "Can't translate linkpath '%s' to UTF-8", linkpath);
        ret = ARCHIVE_WARN;
        hdrcharset = "BINARY";
    }

    /* Store the header encoding first, to be nice to readers. */
    if (hdrcharset != NULL)
        add_pax_attr(&(pax->pax_header), "hdrcharset", hdrcharset);


    /*
     * If name is too long, or has non-ASCII characters, add
     * 'path' to pax extended attrs.  (Note that an unconvertible
     * name must have non-ASCII characters.)
     */
    if (path == NULL) {
        /* We don't have a narrow version, so we have to store
         * the wide version. */
        add_pax_attr_w(&(pax->pax_header), "path", path_w);
        archive_entry_set_pathname(entry_main, "@WidePath");
        need_extension = 1;
    } else if (has_non_ASCII(path_w)) {
        /* We have non-ASCII characters. */
        if (path_w == NULL || hdrcharset != NULL) {
            /* Can't do UTF-8, so store it raw. */
            add_pax_attr(&(pax->pax_header), "path", path);
        } else {
            /* Store UTF-8 */
            add_pax_attr_w(&(pax->pax_header),
                "path", path_w);
        }
        archive_entry_set_pathname(entry_main,
            build_ustar_entry_name(ustar_entry_name,
            path, strlen(path), NULL));
        need_extension = 1;
    } else {
        /* We have an all-ASCII path; we'd like to just store
         * it in the ustar header if it will fit.  Yes, this
         * duplicates some of the logic in
         * write_set_format_ustar.c
         */
        if (strlen(path) <= 100) {
            /* Fits in the old 100-char tar name field. */
        } else {
            /* Find largest suffix that will fit. */
            /* Note: strlen() > 100, so strlen() - 100 - 1 >= 0 */
            suffix = strchr(path + strlen(path) - 100 - 1, '/');
            /* Don't attempt an empty prefix. */
            if (suffix == path)
                suffix = strchr(suffix + 1, '/');
            /* We can put it in the ustar header if it's
             * all ASCII and it's either <= 100 characters
             * or can be split at a '/' into a prefix <=
             * 155 chars and a suffix <= 100 chars.  (Note
             * the strchr() above will return NULL exactly
             * when the path can't be split.)
             */
            if (suffix == NULL       /* Suffix > 100 chars. */
                || suffix[1] == '\0'    /* empty suffix */
                || suffix - path > 155)  /* Prefix > 155 chars */
            {
                if (path_w == NULL || hdrcharset != NULL) {
                    /* Can't do UTF-8, so store it raw. */
                    add_pax_attr(&(pax->pax_header),
                        "path", path);
                } else {
                    /* Store UTF-8 */
                    add_pax_attr_w(&(pax->pax_header),
                        "path", path_w);
                }
                archive_entry_set_pathname(entry_main,
                    build_ustar_entry_name(ustar_entry_name,
                    path, strlen(path), NULL));
                need_extension = 1;
            }
        }
    }

    if (linkpath != NULL) {
        /* If link name is too long or has non-ASCII characters, add
         * 'linkpath' to pax extended attrs. */
        if (strlen(linkpath) > 100 || linkpath_w == NULL
            || linkpath_w == NULL || has_non_ASCII(linkpath_w)) {
            if (linkpath_w == NULL || hdrcharset != NULL)
                /* If the linkpath is not convertible
                 * to wide, or we're encoding in
                 * binary anyway, store it raw. */
                add_pax_attr(&(pax->pax_header),
                    "linkpath", linkpath);
            else
                /* If the link is long or has a
                 * non-ASCII character, store it as a
                 * pax extended attribute. */
                add_pax_attr_w(&(pax->pax_header),
                    "linkpath", linkpath_w);
            if (strlen(linkpath) > 100) {
                if (hardlink != NULL)
                    archive_entry_set_hardlink(entry_main,
                        "././@LongHardLink");
                else
                    archive_entry_set_symlink(entry_main,
                        "././@LongSymLink");
            }
            need_extension = 1;
        }
    }

    /* If file size is too large, add 'size' to pax extended attrs. */
    if (archive_entry_size(entry_main) >= (((int64_t)1) << 33)) {
        add_pax_attr_int(&(pax->pax_header), "size",
            archive_entry_size(entry_main));
        need_extension = 1;
    }

    /* If numeric GID is too large, add 'gid' to pax extended attrs. */
    if ((unsigned int)archive_entry_gid(entry_main) >= (1 << 18)) {
        add_pax_attr_int(&(pax->pax_header), "gid",
            archive_entry_gid(entry_main));
        need_extension = 1;
    }

    /* If group name is too large or has non-ASCII characters, add
     * 'gname' to pax extended attrs. */
    if (gname != NULL) {
        if (strlen(gname) > 31
            || gname_w == NULL
            || has_non_ASCII(gname_w))
        {
            if (gname_w == NULL || hdrcharset != NULL) {
                add_pax_attr(&(pax->pax_header),
                    "gname", gname);
            } else  {
                add_pax_attr_w(&(pax->pax_header),
                    "gname", gname_w);
            }
            need_extension = 1;
        }
    }

    /* If numeric UID is too large, add 'uid' to pax extended attrs. */
    if ((unsigned int)archive_entry_uid(entry_main) >= (1 << 18)) {
        add_pax_attr_int(&(pax->pax_header), "uid",
            archive_entry_uid(entry_main));
        need_extension = 1;
    }

    /* Add 'uname' to pax extended attrs if necessary. */
    if (uname != NULL) {
        if (strlen(uname) > 31
            || uname_w == NULL
            || has_non_ASCII(uname_w))
        {
            if (uname_w == NULL || hdrcharset != NULL) {
                add_pax_attr(&(pax->pax_header),
                    "uname", uname);
            } else {
                add_pax_attr_w(&(pax->pax_header),
                    "uname", uname_w);
            }
            need_extension = 1;
        }
    }

    /*
     * POSIX/SUSv3 doesn't provide a standard key for large device
     * numbers.  I use the same keys here that Joerg Schilling
     * used for 'star.'  (Which, somewhat confusingly, are called
     * "devXXX" even though they code "rdev" values.)  No doubt,
     * other implementations use other keys.  Note that there's no
     * reason we can't write the same information into a number of
     * different keys.
     *
     * Of course, this is only needed for block or char device entries.
     */
    if (archive_entry_filetype(entry_main) == AE_IFBLK
        || archive_entry_filetype(entry_main) == AE_IFCHR) {
        /*
         * If rdevmajor is too large, add 'SCHILY.devmajor' to
         * extended attributes.
         */
        dev_t rdevmajor, rdevminor;
        rdevmajor = archive_entry_rdevmajor(entry_main);
        rdevminor = archive_entry_rdevminor(entry_main);
        if (rdevmajor >= (1 << 18)) {
            add_pax_attr_int(&(pax->pax_header), "SCHILY.devmajor",
                rdevmajor);
            /*
             * Non-strict formatting below means we don't
             * have to truncate here.  Not truncating improves
             * the chance that some more modern tar archivers
             * (such as GNU tar 1.13) can restore the full
             * value even if they don't understand the pax
             * extended attributes.  See my rant below about
             * file size fields for additional details.
             */
            /* archive_entry_set_rdevmajor(entry_main,
               rdevmajor & ((1 << 18) - 1)); */
            need_extension = 1;
        }

        /*
         * If devminor is too large, add 'SCHILY.devminor' to
         * extended attributes.
         */
        if (rdevminor >= (1 << 18)) {
            add_pax_attr_int(&(pax->pax_header), "SCHILY.devminor",
                rdevminor);
            /* Truncation is not necessary here, either. */
            /* archive_entry_set_rdevminor(entry_main,
               rdevminor & ((1 << 18) - 1)); */
            need_extension = 1;
        }
    }

    /*
     * Technically, the mtime field in the ustar header can
     * support 33 bits, but many platforms use signed 32-bit time
     * values.  The cutoff of 0x7fffffff here is a compromise.
     * Yes, this check is duplicated just below; this helps to
     * avoid writing an mtime attribute just to handle a
     * high-resolution timestamp in "restricted pax" mode.
     */
    if (!need_extension &&
        ((archive_entry_mtime(entry_main) < 0)
        || (archive_entry_mtime(entry_main) >= 0x7fffffff)))
        need_extension = 1;

    /* I use a star-compatible file flag attribute. */
    p = archive_entry_fflags_text(entry_main);
    if (!need_extension && p != NULL  &&  *p != '\0')
        need_extension = 1;

    /* If there are non-trivial ACL entries, we need an extension. */
    if (!need_extension && archive_entry_acl_count(entry_original,
        ARCHIVE_ENTRY_ACL_TYPE_ACCESS) > 0)
        need_extension = 1;

    /* If there are non-trivial ACL entries, we need an extension. */
    if (!need_extension && archive_entry_acl_count(entry_original,
        ARCHIVE_ENTRY_ACL_TYPE_DEFAULT) > 0)
        need_extension = 1;

    /* If there are extended attributes, we need an extension */
    if (!need_extension && archive_entry_xattr_count(entry_original) > 0)
        need_extension = 1;

    /*
     * The following items are handled differently in "pax
     * restricted" format.  In particular, in "pax restricted"
     * format they won't be added unless need_extension is
     * already set (we're already generating an extended header, so
     * may as well include these).
     */
    if (a->archive.archive_format != ARCHIVE_FORMAT_TAR_PAX_RESTRICTED ||
        need_extension) {

        if (archive_entry_mtime(entry_main) < 0  ||
            archive_entry_mtime(entry_main) >= 0x7fffffff  ||
            archive_entry_mtime_nsec(entry_main) != 0)
            add_pax_attr_time(&(pax->pax_header), "mtime",
                archive_entry_mtime(entry_main),
                archive_entry_mtime_nsec(entry_main));

        if (archive_entry_ctime(entry_main) != 0  ||
            archive_entry_ctime_nsec(entry_main) != 0)
            add_pax_attr_time(&(pax->pax_header), "ctime",
                archive_entry_ctime(entry_main),
                archive_entry_ctime_nsec(entry_main));

        if (archive_entry_atime(entry_main) != 0 ||
            archive_entry_atime_nsec(entry_main) != 0)
            add_pax_attr_time(&(pax->pax_header), "atime",
                archive_entry_atime(entry_main),
                archive_entry_atime_nsec(entry_main));

        /* Store birth/creationtime only if it's earlier than mtime */
        if (archive_entry_birthtime_is_set(entry_main) &&
            archive_entry_birthtime(entry_main)
            < archive_entry_mtime(entry_main))
            add_pax_attr_time(&(pax->pax_header),
                "LIBARCHIVE.creationtime",
                archive_entry_birthtime(entry_main),
                archive_entry_birthtime_nsec(entry_main));

        /* I use a star-compatible file flag attribute. */
        p = archive_entry_fflags_text(entry_main);
        if (p != NULL  &&  *p != '\0')
            add_pax_attr(&(pax->pax_header), "SCHILY.fflags", p);

        /* I use star-compatible ACL attributes. */
        wp = archive_entry_acl_text_w(entry_original,
            ARCHIVE_ENTRY_ACL_TYPE_ACCESS |
            ARCHIVE_ENTRY_ACL_STYLE_EXTRA_ID);
        if (wp != NULL && *wp != L'\0')
            add_pax_attr_w(&(pax->pax_header),
                "SCHILY.acl.access", wp);
        wp = archive_entry_acl_text_w(entry_original,
            ARCHIVE_ENTRY_ACL_TYPE_DEFAULT |
            ARCHIVE_ENTRY_ACL_STYLE_EXTRA_ID);
        if (wp != NULL && *wp != L'\0')
            add_pax_attr_w(&(pax->pax_header),
                "SCHILY.acl.default", wp);

        /* Include star-compatible metadata info. */
        /* Note: "SCHILY.dev{major,minor}" are NOT the
         * major/minor portions of "SCHILY.dev". */
        add_pax_attr_int(&(pax->pax_header), "SCHILY.dev",
            archive_entry_dev(entry_main));
        add_pax_attr_int(&(pax->pax_header), "SCHILY.ino",
            archive_entry_ino64(entry_main));
        add_pax_attr_int(&(pax->pax_header), "SCHILY.nlink",
            archive_entry_nlink(entry_main));

        /* Store extended attributes */
        archive_write_pax_header_xattrs(pax, entry_original);
    }

    /* Only regular files have data. */
    if (archive_entry_filetype(entry_main) != AE_IFREG)
        archive_entry_set_size(entry_main, 0);

    /*
     * Pax-restricted does not store data for hardlinks, in order
     * to improve compatibility with ustar.
     */
    if (a->archive.archive_format != ARCHIVE_FORMAT_TAR_PAX_INTERCHANGE &&
        hardlink != NULL)
        archive_entry_set_size(entry_main, 0);

    /*
     * XXX Full pax interchange format does permit a hardlink
     * entry to have data associated with it.  I'm not supporting
     * that here because the client expects me to tell them whether
     * or not this format expects data for hardlinks.  If I
     * don't check here, then every pax archive will end up with
     * duplicated data for hardlinks.  Someday, there may be
     * need to select this behavior, in which case the following
     * will need to be revisited. XXX
     */
    if (hardlink != NULL)
        archive_entry_set_size(entry_main, 0);

    /* Format 'ustar' header for main entry.
     *
     * The trouble with file size: If the reader can't understand
     * the file size, they may not be able to locate the next
     * entry and the rest of the archive is toast.  Pax-compliant
     * readers are supposed to ignore the file size in the main
     * header, so the question becomes how to maximize portability
     * for readers that don't support pax attribute extensions.
     * For maximum compatibility, I permit numeric extensions in
     * the main header so that the file size stored will always be
     * correct, even if it's in a format that only some
     * implementations understand.  The technique used here is:
     *
     *  a) If possible, follow the standard exactly.  This handles
     *  files up to 8 gigabytes minus 1.
     *
     *  b) If that fails, try octal but omit the field terminator.
     *  That handles files up to 64 gigabytes minus 1.
     *
     *  c) Otherwise, use base-256 extensions.  That handles files
     *  up to 2^63 in this implementation, with the potential to
     *  go up to 2^94.  That should hold us for a while. ;-)
     *
     * The non-strict formatter uses similar logic for other
     * numeric fields, though they're less critical.
     */
    __archive_write_format_header_ustar(a, ustarbuff, entry_main, -1, 0);

    /* If we built any extended attributes, write that entry first. */
    if (archive_strlen(&(pax->pax_header)) > 0) {
        struct archive_entry *pax_attr_entry;
        time_t s;
        uid_t uid;
        gid_t gid;
        mode_t mode;
        long ns;

        pax_attr_entry = archive_entry_new();
        p = archive_entry_pathname(entry_main);
        archive_entry_set_pathname(pax_attr_entry,
            build_pax_attribute_name(pax_entry_name, p));
        archive_entry_set_size(pax_attr_entry,
            archive_strlen(&(pax->pax_header)));
        /* Copy uid/gid (but clip to ustar limits). */
        uid = archive_entry_uid(entry_main);
        if ((unsigned int)uid >= 1 << 18)
            uid = (uid_t)(1 << 18) - 1;
        archive_entry_set_uid(pax_attr_entry, uid);
        gid = archive_entry_gid(entry_main);
        if ((unsigned int)gid >= 1 << 18)
            gid = (gid_t)(1 << 18) - 1;
        archive_entry_set_gid(pax_attr_entry, gid);
        /* Copy mode over (but not setuid/setgid bits) */
        mode = archive_entry_mode(entry_main);
#ifdef S_ISUID
        mode &= ~S_ISUID;
#endif
#ifdef S_ISGID
        mode &= ~S_ISGID;
#endif
#ifdef S_ISVTX
        mode &= ~S_ISVTX;
#endif
        archive_entry_set_mode(pax_attr_entry, mode);

        /* Copy uname/gname. */
        archive_entry_set_uname(pax_attr_entry,
            archive_entry_uname(entry_main));
        archive_entry_set_gname(pax_attr_entry,
            archive_entry_gname(entry_main));

        /* Copy mtime, but clip to ustar limits. */
        s = archive_entry_mtime(entry_main);
        ns = archive_entry_mtime_nsec(entry_main);
        if (s < 0) { s = 0; ns = 0; }
        if (s > 0x7fffffff) { s = 0x7fffffff; ns = 0; }
        archive_entry_set_mtime(pax_attr_entry, s, ns);

        /* Ditto for atime. */
        s = archive_entry_atime(entry_main);
        ns = archive_entry_atime_nsec(entry_main);
        if (s < 0) { s = 0; ns = 0; }
        if (s > 0x7fffffff) { s = 0x7fffffff; ns = 0; }
        archive_entry_set_atime(pax_attr_entry, s, ns);

        /* Standard ustar doesn't support ctime. */
        archive_entry_set_ctime(pax_attr_entry, 0, 0);

        r = __archive_write_format_header_ustar(a, paxbuff,
            pax_attr_entry, 'x', 1);

        archive_entry_free(pax_attr_entry);

        /* Note that the 'x' header shouldn't ever fail to format */
        if (r != 0) {
            const char *msg = "archive_write_pax_header: "
                "'x' header failed?!  This can't happen.\n";
            size_t u = write(2, msg, strlen(msg));
            (void)u; /* UNUSED */
            exit(1);
        }
        r = (a->compressor.write)(a, paxbuff, 512);
        if (r != ARCHIVE_OK) {
            pax->entry_bytes_remaining = 0;
            pax->entry_padding = 0;
            return (ARCHIVE_FATAL);
        }

        pax->entry_bytes_remaining = archive_strlen(&(pax->pax_header));
        pax->entry_padding = 0x1ff & (-(int64_t)pax->entry_bytes_remaining);

        r = (a->compressor.write)(a, pax->pax_header.s,
            archive_strlen(&(pax->pax_header)));
        if (r != ARCHIVE_OK) {
            /* If a write fails, we're pretty much toast. */
            return (ARCHIVE_FATAL);
        }
        /* Pad out the end of the entry. */
        r = write_nulls(a, pax->entry_padding);
        if (r != ARCHIVE_OK) {
            /* If a write fails, we're pretty much toast. */
            return (ARCHIVE_FATAL);
        }
        pax->entry_bytes_remaining = pax->entry_padding = 0;
    }

    /* Write the header for main entry. */
    r = (a->compressor.write)(a, ustarbuff, 512);
    if (r != ARCHIVE_OK)
        return (r);

    /*
     * Inform the client of the on-disk size we're using, so
     * they can avoid unnecessarily writing a body for something
     * that we're just going to ignore.
     */
    archive_entry_set_size(entry_original, archive_entry_size(entry_main));
    pax->entry_bytes_remaining = archive_entry_size(entry_main);
    pax->entry_padding = 0x1ff & (-(int64_t)pax->entry_bytes_remaining);
    archive_entry_free(entry_main);

    return (ret);
}
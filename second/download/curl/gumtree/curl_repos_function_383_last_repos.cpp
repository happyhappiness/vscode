static void set_features(void)
{
    int status;
    char unix_shell_name[255];
    int use_unix_settings = 1;

    status = sys_trnlnm("GNV$UNIX_SHELL",
                        unix_shell_name, sizeof unix_shell_name -1);
    if (!$VMS_STATUS_SUCCESS(status)) {
        unix_shell_name[0] = 0;
        use_unix_settings = 0;
    }

    /* ACCESS should check ACLs or it is lying. */
    set_feature_default("DECC$ACL_ACCESS_CHECK", ENABLE);

    /* We always want the new parse style */
    set_feature_default ("DECC$ARGV_PARSE_STYLE" , ENABLE);


    /* Unless we are in POSIX compliant mode, we want the old POSIX root
     * enabled.
     */
    set_feature_default("DECC$DISABLE_POSIX_ROOT", DISABLE);

    /* EFS charset, means UTF-8 support */
    /* VTF-7 support is controlled by a feature setting called UTF8 */
    set_feature_default ("DECC$EFS_CHARSET", ENABLE);
    set_feature_default ("DECC$EFS_CASE_PRESERVE", ENABLE);

    /* Support timestamps when available */
    set_feature_default ("DECC$EFS_FILE_TIMESTAMPS", ENABLE);

    /* Cache environment variables - performance improvements */
    set_feature_default ("DECC$ENABLE_GETENV_CACHE", ENABLE);

    /* Start out with new file attribute inheritance */
#ifdef __VAX
    set_feature_default ("DECC$EXEC_FILEATTR_INHERITANCE", "2");
#else
    set_feature_default ("DECC$EXEC_FILEATTR_INHERITANCE", 2);
#endif

    /* Don't display trailing dot after files without type */
    set_feature_default ("DECC$READDIR_DROPDOTNOTYPE", ENABLE);

    /* For standard output channels buffer output until terminator */
    /* Gets rid of output logs with single character lines in them. */
    set_feature_default ("DECC$STDIO_CTX_EOL", ENABLE);

    /* Fix mv aa.bb aa  */
    set_feature_default ("DECC$RENAME_NO_INHERIT", ENABLE);

    if (use_unix_settings) {

        /* POSIX requires that open files be able to be removed */
        set_feature_default ("DECC$ALLOW_REMOVE_OPEN_FILES", ENABLE);

        /* Default to outputting Unix filenames in VMS routines */
        set_feature_default ("DECC$FILENAME_UNIX_ONLY", ENABLE);
        /* FILENAME_UNIX_ONLY Implicitly sets */
        /* decc$disable_to_vms_logname_translation */

        set_feature_default ("DECC$FILE_PERMISSION_UNIX", ENABLE);

        set_feature_default ("DECC$FILE_SHARING", ENABLE);

        set_feature_default ("DECC$FILE_OWNER_UNIX", ENABLE);
        set_feature_default ("DECC$POSIX_SEEK_STREAM_FILE", ENABLE);

    } else {
        set_feature_default("DECC$FILENAME_UNIX_REPORT", ENABLE);
    }

    /* When reporting Unix filenames, glob the same way */
    set_feature_default ("DECC$GLOB_UNIX_STYLE", ENABLE);

    /* The VMS version numbers on Unix filenames is incompatible with most */
    /* ported packages. */
    set_feature_default("DECC$FILENAME_UNIX_NO_VERSION", ENABLE);

    /* The VMS version numbers on Unix filenames is incompatible with most */
    /* ported packages. */
    set_feature_default("DECC$UNIX_PATH_BEFORE_LOGNAME", ENABLE);

    /* Set strtol to proper behavior */
    set_feature_default("DECC$STRTOL_ERANGE", ENABLE);

    /* Commented here to prevent future bugs:  A program or user should */
    /* never ever enable DECC$POSIX_STYLE_UID. */
    /* It will probably break all code that accesses UIDs */
    /*  do_not_set_default ("DECC$POSIX_STYLE_UID", TRUE); */
}
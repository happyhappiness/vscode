static void show_overrides(const command_rec *pc, module *pm)
{
    int n = 0;

    printf("\tAllowed in *.conf ");
    if ((pc->req_override & (OR_OPTIONS | OR_FILEINFO | OR_INDEXES))
        || ((pc->req_override & RSRC_CONF)
        && ((pc->req_override & (ACCESS_CONF | OR_AUTHCFG | OR_LIMIT))))) {
        printf("anywhere");
    }
    else if (pc->req_override & RSRC_CONF) {
        printf("only outside <Directory>, <Files> or <Location>");
    }
    else {
        printf("only inside <Directory>, <Files> or <Location>");
    }

    /* Warn if the directive is allowed inside <Directory> or .htaccess
     * but module doesn't support per-dir configuration
     */
    if ((pc->req_override & (OR_ALL | ACCESS_CONF)) && !pm->create_dir_config)
        printf(" [no per-dir config]");

    if (pc->req_override & OR_ALL) {
        printf(" and in .htaccess\n\twhen AllowOverride");

        if ((pc->req_override & OR_ALL) == OR_ALL) {
            printf(" isn't None");
        }
        else {
            printf(" includes ");

            if (pc->req_override & OR_AUTHCFG) {
                if (n++)
                    printf(" or ");

                printf("AuthConfig");
            }

            if (pc->req_override & OR_LIMIT) {
                if (n++)
                    printf(" or ");

                printf("Limit");
            }

            if (pc->req_override & OR_OPTIONS) {
                if (n++)
                    printf(" or ");

                printf("Options");
            }

            if (pc->req_override & OR_FILEINFO) {
                if (n++)
                    printf(" or ");

                printf("FileInfo");
            }

            if (pc->req_override & OR_INDEXES) {
                if (n++)
                    printf(" or ");

                printf("Indexes");
            }
        }
    }

    printf("\n");
}
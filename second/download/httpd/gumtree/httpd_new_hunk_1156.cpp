                           level,
                           perdir ? "[perdir " : "",
                           perdir ? perdir : "",
                           perdir ? "] ": "",
                           text);

    nbytes = strlen(logline);
    apr_file_write(conf->rewritelogfp, logline, &nbytes);

    return;
}
#endif /* !REWRITELOG_DISABLED */


/*

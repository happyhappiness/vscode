                }
            }
        } else {
            const char *file = apr_pstrcat(pool, dir, "/", dirent.name, NULL);
            rv = apr_file_remove(file, pool);
            if (APR_SUCCESS != rv) {
                char errmsg[120];
                apr_file_printf(errfile,
                        "Could not remove file '%s': %s" APR_EOL_STR, file,
                        apr_strerror(rv, errmsg, sizeof errmsg));
                break;
            }
        }
    }

    apr_dir_close(dirp);

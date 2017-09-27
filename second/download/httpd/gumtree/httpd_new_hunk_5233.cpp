                }
            }
        } else {
            const char *file = apr_pstrcat(pool, dir, "/", dirent.name, NULL);
            rv = apr_file_remove(file, pool);
            if (APR_SUCCESS != rv) {
                apr_file_printf(errfile,
                        "Could not remove file '%s': %pm" APR_EOL_STR, file,
                        &rv);
                break;
            }
        }
    }

    apr_dir_close(dirp);

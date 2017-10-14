apr_file_printf(out, "ChrootDir: \"%s\"%s\n",
                        ap_unixd_config.chroot_dir, no_root);
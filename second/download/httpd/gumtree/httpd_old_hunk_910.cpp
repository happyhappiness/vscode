                    apr_file_close(f);
                    suppress_sig = 1;
                }
            }
        }
    }
    
    if (!suppress_sig) {
        ap_rputs(ap_psignature("", r), r);
    }
    if (!suppress_post) {
        ap_rputs("</body></html>\n", r);
    }

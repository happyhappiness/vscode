            memcpy((char *) finfo, (const char *) &rr->finfo,
                   sizeof(rr->finfo));
            ap_destroy_sub_req(rr);
            return 0;
        }
        else {
            ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                        "unable to get information about \"%s\" "
                        "in parsed file %s",
                        tag_val, r->filename);
            ap_destroy_sub_req(rr);
            return -1;
        }
    }
    else {
        ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                    "unknown parameter \"%s\" to tag %s in %s",
                    tag, directive, r->filename);
        return -1;
    }
}


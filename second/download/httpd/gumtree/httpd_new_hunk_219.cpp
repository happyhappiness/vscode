            }
        }
        else if (!strcmp(tag, "done")) {
            return 0;
        }
        else {
            ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
                        "unknown parameter \"%s\" to tag config in %s",
                        tag, r->filename);
            ap_rputs(error, r);
        }
    }
}


static int find_file(request_rec *r, const char *directive, const char *tag,
                     char *tag_val, struct stat *finfo, const char *error)
{
    char *to_send;
    request_rec *rr;
    int ret=0;

    if (!strcmp(tag, "file")) {
        ap_getparents(tag_val);    /* get rid of any nasties */
        
        rr = ap_sub_req_lookup_file(tag_val, r);

        if (rr->status == HTTP_OK && rr->finfo.st_mode != 0) {
            to_send = rr->filename;
            if ((ret = stat(to_send, finfo)) == -1) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, r,
                            "unable to get information about \"%s\" "
                            "in parsed file %s",
                            to_send, r->filename);
                ap_rputs(error, r);
            }
        }
        else {
            ret = -1;
            ap_log_rerror(APLOG_MARK, APLOG_ERR, r,
                        "unable to lookup information about \"%s\" "
                        "in parsed file %s",
                        tag_val, r->filename);
            ap_rputs(error, r);
        }
        
        ap_destroy_sub_req(rr);
        
        return ret;
    }
    else if (!strcmp(tag, "virtual")) {
        rr = ap_sub_req_lookup_uri(tag_val, r);

        if (rr->status == HTTP_OK && rr->finfo.st_mode != 0) {
            memcpy((char *) finfo, (const char *) &rr->finfo,
                   sizeof(struct stat));
            ap_destroy_sub_req(rr);
            return 0;
        }
        else {
            ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
                        "unable to get information about \"%s\" "
                        "in parsed file %s",
                        tag_val, r->filename);
            ap_rputs(error, r);
            ap_destroy_sub_req(rr);
            return -1;
        }
    }
    else {
        ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
                    "unknown parameter \"%s\" to tag %s in %s",
                    tag, directive, r->filename);
        ap_rputs(error, r);
        return -1;
    }
}

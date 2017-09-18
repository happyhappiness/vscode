            dav_close_propdb(propdb);

            /* undo any auto-checkout */
            dav_auto_checkin(r, resource, 1 /*undo*/, 0 /*unlock*/, &av_info);

            /* This supplies additional information for the default message. */
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "A \"prop\" element is missing inside "
                          "the propertyupdate command.");
            return HTTP_BAD_REQUEST;
        }

        for (one_prop = prop_group->first_child; one_prop;

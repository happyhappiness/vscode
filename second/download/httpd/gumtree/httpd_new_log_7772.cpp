r(APLOG_MARK, APLOG_TRACE1, 0, r,
                  "from form: user: %s, pw: %s, method: %s, mimetype: %s, location: %s",
                  sent_user ? *sent_user : "<null>", sent_pw ? *sent_pw : "<null>",
                  sent_method ? *sent_method : "<null>",
                  sent_mimetype ? *sent_mimetype : "<null>",
                  sent_loc ? *sent_loc : "<null>");
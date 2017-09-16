	}

    }

    if (

    /* username is OK */

	   (res == OK)

    /* password been filled out ? */

	   && ((!sec->auth_anon_mustemail) || strlen(send_pw))

    /* does the password look like an email address ? */

	   && ((!sec->auth_anon_verifyemail)

	       || ((strpbrk("@", send_pw) != NULL)

		   && (strpbrk(".", send_pw) != NULL)))) {

	if (sec->auth_anon_logemail && ap_is_initial_req(r)) {

	    ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_INFO, r->server,

			"Anonymous: Passwd <%s> Accepted",

			send_pw ? send_pw : "\'none\'");

	}

	return OK;

    }

    else {

	if (sec->auth_anon_authoritative) {

	    ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,

			"Anonymous: Authoritative, Passwd <%s> not accepted",

			send_pw ? send_pw : "\'none\'");

	    return AUTH_REQUIRED;

	}

	/* Drop out the bottom to return DECLINED */

    }



    return DECLINED;

-- apache_1.3.0/src/modules/standard/mod_auth.c	1998-04-11 20:00:44.000000000 +0800


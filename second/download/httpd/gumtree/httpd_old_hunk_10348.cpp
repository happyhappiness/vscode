        break;
    }
    return strcmp(c1->name, c2->name);
}


static int index_directory(request_rec *r, autoindex_config_rec * autoindex_conf)
{
    char *title_name = ap_escape_html(r->pool, r->uri);
    char *title_endp;
    char *name = r->filename;

    DIR *d;
    struct DIR_TYPE *dstruct;
    int num_ent = 0, x;
    struct ent *head, *p;
    struct ent **ar = NULL;
    char *tmp;
    const char *qstring;
    int autoindex_opts = find_opts(autoindex_conf, r);
    char keyid;
    char direction;

    if (!(d = ap_popendir(r->pool, name))) {
	ap_log_error(APLOG_MARK, APLOG_ERR, r->server,
		    "Can't open directory for index: %s", r->filename);
	return HTTP_FORBIDDEN;
    }

    r->content_type = "text/html";


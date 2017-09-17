
#define BY_ENCODING &c_by_encoding
#define BY_TYPE &c_by_type
#define BY_PATH &c_by_path

/*
 * Return true if the specified string refers to the parent directory (i.e.,
 * matches ".." or "../").  Hopefully this one call is significantly less
 * expensive than multiple strcmp() calls.
 */
static ap_inline int is_parent(const char *name)
{
    /*
     * Now, IFF the first two bytes are dots, and the third byte is either
     * EOS (\0) or a slash followed by EOS, we have a match.
     */
    if (((name[0] == '.') && (name[1] == '.'))
	&& ((name[2] == '\0')
	    || ((name[2] == '/') && (name[3] == '\0')))) {
        return 1;
    }
    return 0;
}

/*
 * This routine puts the standard HTML header at the top of the index page.
 * We include the DOCTYPE because we may be using features therefrom (i.e.,
 * HEIGHT and WIDTH attributes on the icons if we're FancyIndexing).
 */
static void emit_preamble(request_rec *r, char *title)
{
    ap_rvputs(r, "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 3.2 Final//EN\">\n",
	      "<HTML>\n <HEAD>\n  <TITLE>Index of ", title,
	      "</TITLE>\n </HEAD>\n <BODY>\n", NULL);
}

static void push_item(array_header *arr, char *type, char *to, char *path,
		      char *data)
{
    struct item *p = (struct item *) ap_push_array(arr);

    if (!to) {
	to = "";
    }
    if (!path) {
	path = "";
    }

    p->type = type;
    p->data = data ? ap_pstrdup(arr->pool, data) : NULL;
    p->apply_path = ap_pstrcat(arr->pool, path, "*", NULL);

    if ((type == BY_PATH) && (!ap_is_matchexp(to))) {
	p->apply_to = ap_pstrcat(arr->pool, "*", to, NULL);
    }
    else if (to) {
	p->apply_to = ap_pstrdup(arr->pool, to);
    }
    else {
	p->apply_to = NULL;
    }
}

static const char *add_alt(cmd_parms *cmd, void *d, char *alt, char *to)
{
    if (cmd->info == BY_PATH) {
        if (!strcmp(to, "**DIRECTORY**")) {
	    to = "^^DIRECTORY^^";
	}
    }
    if (cmd->info == BY_ENCODING) {
	ap_str_tolower(to);
    }

    push_item(((autoindex_config_rec *) d)->alt_list, cmd->info, to,
	      cmd->path, alt);
    return NULL;
}

static const char *add_icon(cmd_parms *cmd, void *d, char *icon, char *to)
{
    char *iconbak = ap_pstrdup(cmd->pool, icon);

static const char end_location_section[] = "</Location>";

static const char end_locationmatch_section[] = "</LocationMatch>";

static const char end_files_section[] = "</Files>";

static const char end_filesmatch_section[] = "</FilesMatch>";

static const char end_virtualhost_section[] = "</VirtualHost>";

static const char end_ifmodule_section[] = "</IfModule>";

static const char end_ifdefine_section[] = "</IfDefine>";





API_EXPORT(const char *) ap_check_cmd_context(cmd_parms *cmd,

					      unsigned forbidden)

{

    const char *gt = (cmd->cmd->name[0] == '<'

		      && cmd->cmd->name[strlen(cmd->cmd->name)-1] != '>')

                         ? ">" : "";



    if ((forbidden & NOT_IN_VIRTUALHOST) && cmd->server->is_virtual) {

	return ap_pstrcat(cmd->pool, cmd->cmd->name, gt,

			  " cannot occur within <VirtualHost> section", NULL);

    }



    if ((forbidden & NOT_IN_LIMIT) && cmd->limited != -1) {

	return ap_pstrcat(cmd->pool, cmd->cmd->name, gt,

			  " cannot occur within <Limit> section", NULL);

    }



    if ((forbidden & NOT_IN_DIR_LOC_FILE) == NOT_IN_DIR_LOC_FILE

	&& cmd->path != NULL) {

	return ap_pstrcat(cmd->pool, cmd->cmd->name, gt,

			  " cannot occur within <Directory/Location/Files> "

			  "section", NULL);

    }

    

    if (((forbidden & NOT_IN_DIRECTORY)

	 && (cmd->end_token == end_directory_section

	     || cmd->end_token == end_directorymatch_section)) 

	|| ((forbidden & NOT_IN_LOCATION)

	    && (cmd->end_token == end_location_section

		|| cmd->end_token == end_locationmatch_section)) 

	|| ((forbidden & NOT_IN_FILES)

	    && (cmd->end_token == end_files_section

		|| cmd->end_token == end_filesmatch_section))) {

	return ap_pstrcat(cmd->pool, cmd->cmd->name, gt,

			  " cannot occur within <", cmd->end_token+2,

			  " section", NULL);

    }



    return NULL;

}



static const char *set_access_name(cmd_parms *cmd, void *dummy, char *arg)

{

    void *sconf = cmd->server->module_config;

    core_server_config *conf = ap_get_module_config(sconf, &core_module);



    const char *err = ap_check_cmd_context(cmd,

					   NOT_IN_DIR_LOC_FILE|NOT_IN_LIMIT);

    if (err != NULL) {

        return err;

    }



    conf->access_name = ap_pstrdup(cmd->pool, arg);

    return NULL;

}



static const char *set_document_root(cmd_parms *cmd, void *dummy, char *arg)

{

    void *sconf = cmd->server->module_config;

    core_server_config *conf = ap_get_module_config(sconf, &core_module);

  

    const char *err = ap_check_cmd_context(cmd,

					   NOT_IN_DIR_LOC_FILE|NOT_IN_LIMIT);

    if (err != NULL) {

        return err;

    }



    arg = ap_os_canonical_filename(cmd->pool, arg);

    if (!ap_is_directory(arg)) {

	if (cmd->server->is_virtual) {

	    fprintf(stderr, "Warning: DocumentRoot [%s] does not exist\n",

		    arg);

	}

	else {

	    return "DocumentRoot must be a directory";

	}

    }

    

    conf->ap_document_root = arg;

    return NULL;

}



static const char *set_error_document(cmd_parms *cmd, core_dir_config *conf,

				      char *line)

{

    int error_number, index_number, idx500;

    char *w;

                

    const char *err = ap_check_cmd_context(cmd, NOT_IN_LIMIT);

    if (err != NULL) {

        return err;

    }



    /* 1st parameter should be a 3 digit number, which we recognize;

     * convert it into an array index

     */

  

    w = ap_getword_conf_nc(cmd->pool, &line);

    error_number = atoi(w);



    idx500 = ap_index_of_response(HTTP_INTERNAL_SERVER_ERROR);



    if (error_number == HTTP_INTERNAL_SERVER_ERROR) {

        index_number = idx500;

    }

    else if ((index_number = ap_index_of_response(error_number)) == idx500) {

        return ap_pstrcat(cmd->pool, "Unsupported HTTP response code ",

			  w, NULL);

    }

                

    /* Store it... */



    if (conf->response_code_strings == NULL) {

	conf->response_code_strings =

	    ap_pcalloc(cmd->pool,

		       sizeof(*conf->response_code_strings) * RESPONSE_CODES);

    }

    conf->response_code_strings[index_number] = ap_pstrdup(cmd->pool, line);



    return NULL;

}



/* access.conf commands...

 *


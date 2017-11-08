dav_error * dav_get_locktoken_list(request_rec *r, dav_locktoken_list **ltl) 
{
    dav_error *err;
    dav_if_header *if_header;
    dav_if_state_list *if_state;
    dav_locktoken_list *lock_token = NULL;		
	
    *ltl = NULL;

    if ((err = dav_process_if_header(r, &if_header)) != NULL) {
	/* ### add a higher-level description? */
	return err;
    }
 			
    while (if_header != NULL) {
	if_state = if_header->state;	/* Begining of the if_state linked list */
	while (if_state != NULL)	{
	    if (if_state->condition == DAV_IF_COND_NORMAL
	        && if_state->type == dav_if_opaquelock) {
		lock_token = apr_pcalloc(r->pool, sizeof(dav_locktoken_list));
		lock_token->locktoken = if_state->locktoken;
		lock_token->next = *ltl;
		*ltl = lock_token;
	    }
	    if_state = if_state->next; 
	}
	if_header = if_header->next;
    }
    if (*ltl == NULL) {
	/* No nodes added */
	return dav_new_error(r->pool, HTTP_BAD_REQUEST, DAV_ERR_IF_ABSENT,
			     "No locktokens were specified in the \"If:\" "
			     "header, so the refresh could not be performed.");
    }

    return NULL;
}
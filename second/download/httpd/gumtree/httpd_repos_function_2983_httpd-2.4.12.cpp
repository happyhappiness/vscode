static void *merge_auth_form_dir_config(apr_pool_t * p, void *basev, void *addv)
{
    auth_form_config_rec *new = (auth_form_config_rec *) apr_pcalloc(p, sizeof(auth_form_config_rec));
    auth_form_config_rec *add = (auth_form_config_rec *) addv;
    auth_form_config_rec *base = (auth_form_config_rec *) basev;

    new->providers = !add->providers ? base->providers : add->providers;
    new->authoritative = (add->authoritative_set == 0) ? base->authoritative : add->authoritative;
    new->authoritative_set = add->authoritative_set || base->authoritative_set;
    new->site = (add->site_set == 0) ? base->site : add->site;
    new->site_set = add->site_set || base->site_set;
    new->username = (add->username_set == 0) ? base->username : add->username;
    new->username_set = add->username_set || base->username_set;
    new->password = (add->password_set == 0) ? base->password : add->password;
    new->password_set = add->password_set || base->password_set;
    new->location = (add->location_set == 0) ? base->location : add->location;
    new->location_set = add->location_set || base->location_set;
    new->form_size = (add->form_size_set == 0) ? base->form_size : add->form_size;
    new->form_size_set = add->form_size_set || base->form_size_set;
    new->fakebasicauth = (add->fakebasicauth_set == 0) ? base->fakebasicauth : add->fakebasicauth;
    new->fakebasicauth_set = add->fakebasicauth_set || base->fakebasicauth_set;
    new->method = (add->method_set == 0) ? base->method : add->method;
    new->method_set = add->method_set || base->method_set;
    new->mimetype = (add->mimetype_set == 0) ? base->mimetype : add->mimetype;
    new->mimetype_set = add->mimetype_set || base->mimetype_set;
    new->body = (add->body_set == 0) ? base->body : add->body;
    new->body_set = add->body_set || base->body_set;
    new->disable_no_store = (add->disable_no_store_set == 0) ? base->disable_no_store : add->disable_no_store;
    new->disable_no_store_set = add->disable_no_store_set || base->disable_no_store_set;
    new->loginsuccess = (add->loginsuccess_set == 0) ? base->loginsuccess : add->loginsuccess;
    new->loginsuccess_set = add->loginsuccess_set || base->loginsuccess_set;
    new->loginrequired = (add->loginrequired_set == 0) ? base->loginrequired : add->loginrequired;
    new->loginrequired_set = add->loginrequired_set || base->loginrequired_set;
    new->logout = (add->logout_set == 0) ? base->logout : add->logout;
    new->logout_set = add->logout_set || base->logout_set;

    return new;
}
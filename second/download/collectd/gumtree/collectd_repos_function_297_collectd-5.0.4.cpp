static void camqp_config_free (void *ptr) /* {{{ */
{
    camqp_config_t *conf = ptr;

    if (conf == NULL)
        return;

    camqp_close_connection (conf);

    sfree (conf->name);
    sfree (conf->host);
    sfree (conf->vhost);
    sfree (conf->user);
    sfree (conf->password);
    sfree (conf->exchange);
    sfree (conf->exchange_type);
    sfree (conf->queue);
    sfree (conf->routing_key);

    sfree (conf);
}
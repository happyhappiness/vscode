static void
free_UrlHelperTimeout(SquidConfig::UrlHelperTimeout *config)
{
    Config.Timeout.urlRewrite = 0;
    config->action = 0;
    safe_free(config->response);
}
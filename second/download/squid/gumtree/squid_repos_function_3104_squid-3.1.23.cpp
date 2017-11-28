void
errorStateFree(ErrorState * err)
{
    HTTPMSGUNLOCK(err->request);
    safe_free(err->redirect_url);
    safe_free(err->url);
    safe_free(err->request_hdrs);
    wordlistDestroy(&err->ftp.server_msg);
    safe_free(err->ftp.request);
    safe_free(err->ftp.reply);
    AUTHUSERREQUESTUNLOCK(err->auth_user_request, "errstate");
    safe_free(err->err_msg);
#if USE_ERR_LOCALES
    if (err->err_language != Config.errorDefaultLanguage)
#endif
        safe_free(err->err_language);
#if USE_SSL
    delete err->detail;
#endif
    delete err;
}
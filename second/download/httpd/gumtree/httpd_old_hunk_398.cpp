 * that environment variable, if it exists. If the
 * environment value does not exist, leave the ${ENV}
 * construct alone; it means something else.
 */
AP_DECLARE(const char *) ap_resolve_env(apr_pool_t *p, const char * word)
{
       char tmp[ MAX_STRING_LEN ];
       const char *s, *e;
       tmp[0] = '\0';

       if (!(s=ap_strchr_c(word,'$')))
               return word;

       do {
               /* XXX - relies on strncat() to add '\0'
                */
               strncat(tmp,word,s - word);
               if ((s[1] == '{') && (e=ap_strchr_c(s,'}'))) {
                       const char *e2 = e;
                       char *var;
                       word = e + 1;
                       var = apr_pstrndup(p, s+2, e2-(s+2));
                       e = getenv(var);
                       if (e) {
                           strcat(tmp,e);
                       } else {
                           strncat(tmp, s, e2-s);
                           strcat(tmp,"}");
                       }
               } else {
                       /* ignore invalid strings */
                       word = s+1;
                       strcat(tmp,"$");
               };
       } while ((s=ap_strchr_c(word,'$')));
       strcat(tmp,word);

       return apr_pstrdup(p,tmp);
}
AP_DECLARE(int) ap_cfg_closefile(ap_configfile_t *cfp)
{
#ifdef DEBUG
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, NULL, 
        "Done with config file %s", cfp->name);
#endif

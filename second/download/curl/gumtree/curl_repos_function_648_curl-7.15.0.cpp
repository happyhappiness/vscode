static char *get_netscape_format(const struct Cookie *co)
{
   return aprintf(
     "%s%s\t" /* domain */
     "%s\t"   /* tailmatch */
     "%s\t"   /* path */
     "%s\t"   /* secure */
     "%" FORMAT_OFF_T "\t"   /* expires */
     "%s\t"   /* name */
     "%s",    /* value */
     /* Make sure all domains are prefixed with a dot if they allow
        tailmatching. This is Mozilla-style. */
     (co->tailmatch && co->domain && co->domain[0] != '.')? ".":"",
     co->domain?co->domain:"unknown",
     co->tailmatch?"TRUE":"FALSE",
     co->path?co->path:"/",
     co->secure?"TRUE":"FALSE",
     co->expires,
     co->name,
     co->value?co->value:"");
}
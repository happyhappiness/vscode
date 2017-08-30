 ****************************************************************************/

void Curl_cookie_cleanup(struct CookieInfo *c)

{

  struct Cookie *co;

  struct Cookie *next;

  if(c) {

    if(c->filename)

      free(c->filename);

    co = c->cookies;



    while(co) {

      next = co->next;

      freecookie(co);

      co = next;

    }

    free(c); /* free the base struct as well */

  }

}



/* get_netscape_format()

 *

 * Formats a string for Netscape output file, w/o a newline at the end.

 *

 * Function returns a char * to a formatted line. Has to be free()d

*/

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



/*


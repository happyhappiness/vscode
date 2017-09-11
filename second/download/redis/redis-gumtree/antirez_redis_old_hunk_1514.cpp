 * Example:
 *
 * s = sdsnew("AA...AA.a.aa.aHelloWorld     :::");
 * s = sdstrim(s,"A. :");
 * printf("%s\n", s);
 *
 * Output will be just "Hello World".

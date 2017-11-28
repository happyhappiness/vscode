 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111, USA.
 *
 */

#define _etext etext

#include "squid.h"
#include "util.h"

#if HAVE_STDIO_H
#include <stdio.h>
#endif
#if HAVE_STRING_H
#include <string.h>
#endif
#if HAVE_CTYPE_H
#include <ctype.h>
#endif
#if HAVE_UNISTD_H
#include <unistd.h>
#endif
#if HAVE_MATH_H
#include <math.h>
#endif

void
Tolower(char *q)
{
    char *s = q;


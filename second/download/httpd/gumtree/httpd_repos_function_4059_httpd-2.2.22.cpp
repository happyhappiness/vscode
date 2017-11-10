static int
get_ucp(const uschar **ptrptr, BOOL *negptr, const char **errorptr)
{
int c, i, bot, top;
const uschar *ptr = *ptrptr;
char name[4];

c = *(++ptr);
if (c == 0) goto ERROR_RETURN;

*negptr = FALSE;

/* \P or \p can be followed by a one- or two-character name in {}, optionally
preceded by ^ for negation. */

if (c == '{')
  {
  if (ptr[1] == '^')
    {
    *negptr = TRUE;
    ptr++;
    }
  for (i = 0; i <= 2; i++)
    {
    c = *(++ptr);
    if (c == 0) goto ERROR_RETURN;
    if (c == '}') break;
    name[i] = c;
    }
  if (c !='}')   /* Try to distinguish error cases */
    {
    while (*(++ptr) != 0 && *ptr != '}');
    if (*ptr == '}') goto UNKNOWN_RETURN; else goto ERROR_RETURN;
    }
  name[i] = 0;
  }

/* Otherwise there is just one following character */

else
  {
  name[0] = c;
  name[1] = 0;
  }

*ptrptr = ptr;

/* Search for a recognized property name using binary chop */

bot = 0;
top = sizeof(utt)/sizeof(ucp_type_table);

while (bot < top)
  {
  i = (bot + top)/2;
  c = strcmp(name, utt[i].name);
  if (c == 0) return utt[i].value;
  if (c > 0) bot = i + 1; else top = i;
  }

UNKNOWN_RETURN:
*errorptr = ERR47;
*ptrptr = ptr;
return -1;

ERROR_RETURN:
*errorptr = ERR46;
*ptrptr = ptr;
return -1;
}
static BOOL
is_counted_repeat(const uschar *p, compile_data *cd)
{
if ((cd->ctypes[*p++] & ctype_digit) == 0) return FALSE;
while ((cd->ctypes[*p] & ctype_digit) != 0) p++;
if (*p == '}') return TRUE;

if (*p++ != ',') return FALSE;
if (*p == '}') return TRUE;

if ((cd->ctypes[*p++] & ctype_digit) == 0) return FALSE;
while ((cd->ctypes[*p] & ctype_digit) != 0) p++;
return (*p == '}');
}
static int
find_firstchar(const uschar *code, int *options)
{
register int c = -1;
do {
   int d;
   const uschar *scode = first_significant_code(code + 3, options,
     PCRE_CASELESS, TRUE);
   register int op = *scode;

   if (op >= OP_BRA) op = OP_BRA;

   switch(op)
     {
     default:
     return -1;

     case OP_BRA:
     case OP_ASSERT:
     case OP_ONCE:
     case OP_COND:
     if ((d = find_firstchar(scode, options)) < 0) return -1;
     if (c < 0) c = d; else if (c != d) return -1;
     break;

     case OP_EXACT:       /* Fall through */
     scode++;

     case OP_CHARS:       /* Fall through */
     scode++;

     case OP_PLUS:
     case OP_MINPLUS:
     if (c < 0) c = scode[1]; else if (c != scode[1]) return -1;
     break;
     }

   code += (code[1] << 8) + code[2];
   }
while (*code == OP_ALT);
return c;
}
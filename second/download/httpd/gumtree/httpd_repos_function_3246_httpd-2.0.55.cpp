static BOOL
is_anchored(register const uschar *code, int *options)
{
do {
   const uschar *scode = first_significant_code(code + 3, options,
     PCRE_MULTILINE, FALSE);
   register int op = *scode;
   if (op >= OP_BRA || op == OP_ASSERT || op == OP_ONCE || op == OP_COND)
     { if (!is_anchored(scode, options)) return FALSE; }
   else if ((op == OP_TYPESTAR || op == OP_TYPEMINSTAR) &&
            (*options & PCRE_DOTALL) != 0)
     { if (scode[1] != OP_ANY) return FALSE; }
   else if (op != OP_SOD &&
           ((*options & PCRE_MULTILINE) != 0 || op != OP_CIRC))
     return FALSE;
   code += (code[1] << 8) + code[2];
   }
while (*code == OP_ALT);
return TRUE;
}
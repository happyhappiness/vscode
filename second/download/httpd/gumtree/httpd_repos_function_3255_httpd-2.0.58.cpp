static BOOL
is_startline(const uschar *code)
{
do {
   const uschar *scode = first_significant_code(code + 3, NULL, 0, FALSE);
   register int op = *scode;
   if (op >= OP_BRA || op == OP_ASSERT || op == OP_ONCE || op == OP_COND)
     { if (!is_startline(scode)) return FALSE; }
   else if (op == OP_TYPESTAR || op == OP_TYPEMINSTAR)
     { if (scode[1] != OP_ANY) return FALSE; }
   else if (op != OP_CIRC) return FALSE;
   code += (code[1] << 8) + code[2];
   }
while (*code == OP_ALT);
return TRUE;
}
     ((re->options & PCRE_EXTRA) != 0)? "extra " : "",
     ((re->options & PCRE_UNGREEDY) != 0)? "ungreedy " : "");
   }
 
 if ((re->options & PCRE_FIRSTSET) != 0)
   {
-  if (isprint(re->first_char)) printf("First char = %c\n", re->first_char);
-    else printf("First char = \\x%02x\n", re->first_char);
+  int ch = re->first_byte & 255;
+  const char *caseless = ((re->first_byte & REQ_CASELESS) == 0)? "" : " (caseless)";
+  if (isprint(ch)) printf("First char = %c%s\n", ch, caseless);
+    else printf("First char = \\x%02x%s\n", ch, caseless);
   }
 
 if ((re->options & PCRE_REQCHSET) != 0)
   {
-  if (isprint(re->req_char)) printf("Req char = %c\n", re->req_char);
-    else printf("Req char = \\x%02x\n", re->req_char);
+  int ch = re->req_byte & 255;
+  const char *caseless = ((re->req_byte & REQ_CASELESS) == 0)? "" : " (caseless)";
+  if (isprint(ch)) printf("Req char = %c%s\n", ch, caseless);
+    else printf("Req char = \\x%02x%s\n", ch, caseless);
   }
 
-code_end = code;
-code_base = code = re->code;
-
-while (code < code_end)
-  {
-  int charlength;
-
-  printf("%3d ", code - code_base);
-
-  if (*code >= OP_BRA)
-    {
-    if (*code - OP_BRA > EXTRACT_BASIC_MAX)
-      printf("%3d Bra extra", (code[1] << 8) + code[2]);
-    else
-      printf("%3d Bra %d", (code[1] << 8) + code[2], *code - OP_BRA);
-    code += 2;
-    }
-
-  else switch(*code)
-    {
-    case OP_OPT:
-    printf(" %.2x %s", code[1], OP_names[*code]);
-    code++;
-    break;
-
-    case OP_CHARS:
-    charlength = *(++code);
-    printf("%3d ", charlength);
-    while (charlength-- > 0)
-      if (isprint(c = *(++code))) printf("%c", c); else printf("\\x%02x", c);
-    break;
-
-    case OP_KETRMAX:
-    case OP_KETRMIN:
-    case OP_ALT:
-    case OP_KET:
-    case OP_ASSERT:
-    case OP_ASSERT_NOT:
-    case OP_ASSERTBACK:
-    case OP_ASSERTBACK_NOT:
-    case OP_ONCE:
-    case OP_REVERSE:
-    case OP_BRANUMBER:
-    case OP_COND:
-    case OP_CREF:
-    printf("%3d %s", (code[1] << 8) + code[2], OP_names[*code]);
-    code += 2;
-    break;
-
-    case OP_STAR:
-    case OP_MINSTAR:
-    case OP_PLUS:
-    case OP_MINPLUS:
-    case OP_QUERY:
-    case OP_MINQUERY:
-    case OP_TYPESTAR:
-    case OP_TYPEMINSTAR:
-    case OP_TYPEPLUS:
-    case OP_TYPEMINPLUS:
-    case OP_TYPEQUERY:
-    case OP_TYPEMINQUERY:
-    if (*code >= OP_TYPESTAR)
-      printf("    %s", OP_names[code[1]]);
-    else if (isprint(c = code[1])) printf("    %c", c);
-      else printf("    \\x%02x", c);
-    printf("%s", OP_names[*code++]);
-    break;
-
-    case OP_EXACT:
-    case OP_UPTO:
-    case OP_MINUPTO:
-    if (isprint(c = code[3])) printf("    %c{", c);
-      else printf("    \\x%02x{", c);
-    if (*code != OP_EXACT) printf("0,");
-    printf("%d}", (code[1] << 8) + code[2]);
-    if (*code == OP_MINUPTO) printf("?");
-    code += 3;
-    break;
-
-    case OP_TYPEEXACT:
-    case OP_TYPEUPTO:
-    case OP_TYPEMINUPTO:
-    printf("    %s{", OP_names[code[3]]);
-    if (*code != OP_TYPEEXACT) printf(",");
-    printf("%d}", (code[1] << 8) + code[2]);
-    if (*code == OP_TYPEMINUPTO) printf("?");
-    code += 3;
-    break;
-
-    case OP_NOT:
-    if (isprint(c = *(++code))) printf("    [^%c]", c);
-      else printf("    [^\\x%02x]", c);
-    break;
-
-    case OP_NOTSTAR:
-    case OP_NOTMINSTAR:
-    case OP_NOTPLUS:
-    case OP_NOTMINPLUS:
-    case OP_NOTQUERY:
-    case OP_NOTMINQUERY:
-    if (isprint(c = code[1])) printf("    [^%c]", c);
-      else printf("    [^\\x%02x]", c);
-    printf("%s", OP_names[*code++]);
-    break;
-
-    case OP_NOTEXACT:
-    case OP_NOTUPTO:
-    case OP_NOTMINUPTO:
-    if (isprint(c = code[3])) printf("    [^%c]{", c);
-      else printf("    [^\\x%02x]{", c);
-    if (*code != OP_NOTEXACT) printf(",");
-    printf("%d}", (code[1] << 8) + code[2]);
-    if (*code == OP_NOTMINUPTO) printf("?");
-    code += 3;
-    break;
-
-    case OP_REF:
-    printf("    \\%d", (code[1] << 8) | code[2]);
-    code += 3;
-    goto CLASS_REF_REPEAT;
-
-    case OP_CLASS:
-      {
-      int i, min, max;
-      code++;
-      printf("    [");
-
-      for (i = 0; i < 256; i++)
-        {
-        if ((code[i/8] & (1 << (i&7))) != 0)
-          {
-          int j;
-          for (j = i+1; j < 256; j++)
-            if ((code[j/8] & (1 << (j&7))) == 0) break;
-          if (i == '-' || i == ']') printf("\\");
-          if (isprint(i)) printf("%c", i); else printf("\\x%02x", i);
-          if (--j > i)
-            {
-            printf("-");
-            if (j == '-' || j == ']') printf("\\");
-            if (isprint(j)) printf("%c", j); else printf("\\x%02x", j);
-            }
-          i = j;
-          }
-        }
-      printf("]");
-      code += 32;
-
-      CLASS_REF_REPEAT:
-
-      switch(*code)
-        {
-        case OP_CRSTAR:
-        case OP_CRMINSTAR:
-        case OP_CRPLUS:
-        case OP_CRMINPLUS:
-        case OP_CRQUERY:
-        case OP_CRMINQUERY:
-        printf("%s", OP_names[*code]);
-        break;
-
-        case OP_CRRANGE:
-        case OP_CRMINRANGE:
-        min = (code[1] << 8) + code[2];
-        max = (code[3] << 8) + code[4];
-        if (max == 0) printf("{%d,}", min);
-        else printf("{%d,%d}", min, max);
-        if (*code == OP_CRMINRANGE) printf("?");
-        code += 4;
-        break;
-
-        default:
-        code--;
-        }
-      }
-    break;
-
-    /* Anything else is just a one-node item */
-
-    default:
-    printf("    %s", OP_names[*code]);
-    break;
-    }
-
-  code++;
-  printf("\n");
-  }
-printf("------------------------------------------------------------------\n");
+print_internals(re, stdout);
 
 /* This check is done here in the debugging case so that the code that
 was compiled can be seen. */
 
-if (code - re->code > length)
+if (code - codestart > length)
   {
   *errorptr = ERR23;
   (pcre_free)(re);
   *erroroffset = ptr - (uschar *)pattern;
   return NULL;
   }

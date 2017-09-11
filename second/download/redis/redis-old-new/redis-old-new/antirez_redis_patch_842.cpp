@@ -77,42 +77,44 @@ malloc_write(const char *s)
  * provide a wrapper.
  */
 int
-buferror(char *buf, size_t buflen)
+buferror(int err, char *buf, size_t buflen)
 {
 
 #ifdef _WIN32
 	FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(), 0,
 	    (LPSTR)buf, buflen, NULL);
 	return (0);
 #elif defined(_GNU_SOURCE)
-	char *b = strerror_r(errno, buf, buflen);
+	char *b = strerror_r(err, buf, buflen);
 	if (b != buf) {
 		strncpy(buf, b, buflen);
 		buf[buflen-1] = '\0';
 	}
 	return (0);
 #else
-	return (strerror_r(errno, buf, buflen));
+	return (strerror_r(err, buf, buflen));
 #endif
 }
 
 uintmax_t
-malloc_strtoumax(const char *nptr, char **endptr, int base)
+malloc_strtoumax(const char *restrict nptr, char **restrict endptr, int base)
 {
 	uintmax_t ret, digit;
 	int b;
 	bool neg;
 	const char *p, *ns;
 
+	p = nptr;
 	if (base < 0 || base == 1 || base > 36) {
+		ns = p;
 		set_errno(EINVAL);
-		return (UINTMAX_MAX);
+		ret = UINTMAX_MAX;
+		goto label_return;
 	}
 	b = base;
 
 	/* Swallow leading whitespace and get sign, if any. */
 	neg = false;
-	p = nptr;
 	while (true) {
 		switch (*p) {
 		case '\t': case '\n': case '\v': case '\f': case '\r': case ' ':
@@ -146,7 +148,7 @@ malloc_strtoumax(const char *nptr, char **endptr, int base)
 			if (b == 8)
 				p++;
 			break;
-		case 'x':
+		case 'X': case 'x':
 			switch (p[2]) {
 			case '0': case '1': case '2': case '3': case '4':
 			case '5': case '6': case '7': case '8': case '9':
@@ -164,7 +166,9 @@ malloc_strtoumax(const char *nptr, char **endptr, int base)
 			}
 			break;
 		default:
-			break;
+			p++;
+			ret = 0;
+			goto label_return;
 		}
 	}
 	if (b == 0)
@@ -181,21 +185,29 @@ malloc_strtoumax(const char *nptr, char **endptr, int base)
 		if (ret < pret) {
 			/* Overflow. */
 			set_errno(ERANGE);
-			return (UINTMAX_MAX);
+			ret = UINTMAX_MAX;
+			goto label_return;
 		}
 		p++;
 	}
 	if (neg)
 		ret = -ret;
 
+	if (p == ns) {
+		/* No conversion performed. */
+		set_errno(EINVAL);
+		ret = UINTMAX_MAX;
+		goto label_return;
+	}
+
+label_return:
 	if (endptr != NULL) {
 		if (p == ns) {
 			/* No characters were converted. */
 			*endptr = (char *)nptr;
 		} else
 			*endptr = (char *)p;
 	}
-
 	return (ret);
 }
 
@@ -331,7 +343,7 @@ malloc_vsnprintf(char *str, size_t size, const char *format, va_list ap)
 			APPEND_C(' ');					\
 	}								\
 } while (0)
-#define GET_ARG_NUMERIC(val, len) do {					\
+#define	GET_ARG_NUMERIC(val, len) do {					\
 	switch (len) {							\
 	case '?':							\
 		val = va_arg(ap, int);					\
@@ -354,6 +366,9 @@ malloc_vsnprintf(char *str, size_t size, const char *format, va_list ap)
 	case 'j':							\
 		val = va_arg(ap, intmax_t);				\
 		break;							\
+	case 'j' | 0x80:						\
+		val = va_arg(ap, uintmax_t);				\
+		break;							\
 	case 't':							\
 		val = va_arg(ap, ptrdiff_t);				\
 		break;							\
@@ -385,11 +400,6 @@ malloc_vsnprintf(char *str, size_t size, const char *format, va_list ap)
 			unsigned char len = '?';
 
 			f++;
-			if (*f == '%') {
-				/* %% */
-				APPEND_C(*f);
-				break;
-			}
 			/* Flags. */
 			while (true) {
 				switch (*f) {
@@ -419,6 +429,10 @@ malloc_vsnprintf(char *str, size_t size, const char *format, va_list ap)
 			case '*':
 				width = va_arg(ap, int);
 				f++;
+				if (width < 0) {
+					left_justify = true;
+					width = -width;
+				}
 				break;
 			case '0': case '1': case '2': case '3': case '4':
 			case '5': case '6': case '7': case '8': case '9': {
@@ -428,19 +442,16 @@ malloc_vsnprintf(char *str, size_t size, const char *format, va_list ap)
 				assert(uwidth != UINTMAX_MAX || get_errno() !=
 				    ERANGE);
 				width = (int)uwidth;
-				if (*f == '.') {
-					f++;
-					goto label_precision;
-				} else
-					goto label_length;
 				break;
-			} case '.':
-				f++;
-				goto label_precision;
-			default: goto label_length;
+			} default:
+				break;
 			}
+			/* Width/precision separator. */
+			if (*f == '.')
+				f++;
+			else
+				goto label_length;
 			/* Precision. */
-			label_precision:
 			switch (*f) {
 			case '*':
 				prec = va_arg(ap, int);
@@ -469,16 +480,8 @@ malloc_vsnprintf(char *str, size_t size, const char *format, va_list ap)
 				} else
 					len = 'l';
 				break;
-			case 'j':
-				len = 'j';
-				f++;
-				break;
-			case 't':
-				len = 't';
-				f++;
-				break;
-			case 'z':
-				len = 'z';
+			case 'q': case 'j': case 't': case 'z':
+				len = *f;
 				f++;
 				break;
 			default: break;
@@ -487,6 +490,11 @@ malloc_vsnprintf(char *str, size_t size, const char *format, va_list ap)
 			switch (*f) {
 				char *s;
 				size_t slen;
+			case '%':
+				/* %% */
+				APPEND_C(*f);
+				f++;
+				break;
 			case 'd': case 'i': {
 				intmax_t val JEMALLOC_CC_SILENCE_INIT(0);
 				char buf[D2S_BUFSIZE];
@@ -540,7 +548,7 @@ malloc_vsnprintf(char *str, size_t size, const char *format, va_list ap)
 				assert(len == '?' || len == 'l');
 				assert_not_implemented(len != 'l');
 				s = va_arg(ap, char *);
-				slen = (prec == -1) ? strlen(s) : prec;
+				slen = (prec < 0) ? strlen(s) : prec;
 				APPEND_PADDED_S(s, slen, width, left_justify);
 				f++;
 				break;
@@ -553,8 +561,7 @@ malloc_vsnprintf(char *str, size_t size, const char *format, va_list ap)
 				APPEND_PADDED_S(s, slen, width, left_justify);
 				f++;
 				break;
-			}
-			default: not_implemented();
+			} default: not_reached();
 			}
 			break;
 		} default: {
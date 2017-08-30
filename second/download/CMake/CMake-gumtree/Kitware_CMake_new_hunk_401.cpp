/* This used to be an fputs(), but since the string might contain NUL's,

 * we now use fwrite().

 */

#define ECHO do { if (fwrite( yytext, (size_t) yyleng, 1, yyout )) {} } while (0)

#endif



/* Gets input and stuffs it into "buf".  number of characters read, or YY_NULL,

 * is returned in "result".

 */

#ifndef YY_INPUT

#define YY_INPUT(buf,result,max_size) \

	if ( YY_CURRENT_BUFFER_LVALUE->yy_is_interactive ) \

		{ \

		int c = '*'; \

		size_t n; \

		for ( n = 0; n < max_size && \

			     (c = getc( yyin )) != EOF && c != '\n'; ++n ) \

			buf[n] = (char) c; \

		if ( c == '\n' ) \

			buf[n++] = (char) c; \

		if ( c == EOF && ferror( yyin ) ) \

			YY_FATAL_ERROR( "input in flex scanner failed" ); \

		result = n; \

		} \

	else \

		{ \

		errno=0; \

		while ( (result = (int) fread(buf, 1, max_size, yyin))==0 && ferror(yyin)) \

			{ \

			if( errno != EINTR) \

				{ \

				YY_FATAL_ERROR( "input in flex scanner failed" ); \

				break; \

				} \

			errno=0; \

			clearerr(yyin); \

			} \

		}\

\



#endif


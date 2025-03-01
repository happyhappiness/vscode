static void inspect_link(link_ctx *ctx, const char *s, size_t slen)
{
    /* RFC 5988 <https://tools.ietf.org/html/rfc5988#section-6.2.1>
      Link           = "Link" ":" #link-value
      link-value     = "<" URI-Reference ">" *( ";" link-param )
      link-param     = ( ( "rel" "=" relation-types )
                     | ( "anchor" "=" <"> URI-Reference <"> )
                     | ( "rev" "=" relation-types )
                     | ( "hreflang" "=" Language-Tag )
                     | ( "media" "=" ( MediaDesc | ( <"> MediaDesc <"> ) ) )
                     | ( "title" "=" quoted-string )
                     | ( "title*" "=" ext-value )
                     | ( "type" "=" ( media-type | quoted-mt ) )
                     | ( link-extension ) )
      link-extension = ( parmname [ "=" ( ptoken | quoted-string ) ] )
                     | ( ext-name-star "=" ext-value )
      ext-name-star  = parmname "*" ; reserved for RFC2231-profiled
                                    ; extensions.  Whitespace NOT
                                    ; allowed in between.
      ptoken         = 1*ptokenchar
      ptokenchar     = "!" | "#" | "$" | "%" | "&" | "'" | "("
                     | ")" | "*" | "+" | "-" | "." | "/" | DIGIT
                     | ":" | "<" | "=" | ">" | "?" | "@" | ALPHA
                     | "[" | "]" | "^" | "_" | "`" | "{" | "|"
                     | "}" | "~"
      media-type     = type-name "/" subtype-name
      quoted-mt      = <"> media-type <">
      relation-types = relation-type
                     | <"> relation-type *( 1*SP relation-type ) <">
      relation-type  = reg-rel-type | ext-rel-type
      reg-rel-type   = LOALPHA *( LOALPHA | DIGIT | "." | "-" )
      ext-rel-type   = URI
      
      and from <https://tools.ietf.org/html/rfc5987>
      parmname      = 1*attr-char
      attr-char     = ALPHA / DIGIT
                       / "!" / "#" / "$" / "&" / "+" / "-" / "."
                       / "^" / "_" / "`" / "|" / "~"
     */

     ctx->s = s;
     ctx->slen = slen;
     ctx->i = 0;
     
     while (read_link(ctx)) {
        init_params(ctx);
        while (read_param(ctx)) {
            /* nop */
        }
        add_push(ctx);
        if (!read_sep(ctx)) {
            break;
        }
     }
}
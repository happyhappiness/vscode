{
    case cmListFileLexer_Token_None:
      return "nothing";
    case cmListFileLexer_Token_Space:
      return "space";
    case cmListFileLexer_Token_Newline:
      return "newline";
    case cmListFileLexer_Token_Identifier:
      return "identifier";
    case cmListFileLexer_Token_ParenLeft:
      return "left paren";
    case cmListFileLexer_Token_ParenRight:
      return "right paren";
    case cmListFileLexer_Token_ArgumentUnquoted:
      return "unquoted argument";
    case cmListFileLexer_Token_ArgumentQuoted:
      return "quoted argument";
    case cmListFileLexer_Token_ArgumentBracket:
      return "bracket argument";
    case cmListFileLexer_Token_CommentBracket:
      return "bracket comment";
    case cmListFileLexer_Token_BadCharacter:
      return "bad character";
    case cmListFileLexer_Token_BadBracket:
      return "unterminated bracket";
    case cmListFileLexer_Token_BadString:
      return "unterminated string";
  }
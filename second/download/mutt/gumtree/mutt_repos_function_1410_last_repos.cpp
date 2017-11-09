static int menu_dialog_translate_op (int i)
{
  switch (i)
  {
    case OP_NEXT_ENTRY:   
      return OP_NEXT_LINE;
    case OP_PREV_ENTRY:	  
      return OP_PREV_LINE;
    case OP_CURRENT_TOP:   case OP_FIRST_ENTRY:  
      return OP_TOP_PAGE;
    case OP_CURRENT_BOTTOM:    case OP_LAST_ENTRY:	  
      return OP_BOTTOM_PAGE;
    case OP_CURRENT_MIDDLE: 
      return OP_MIDDLE_PAGE; 
  }
  
  return i;
}
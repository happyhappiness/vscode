{
      int x;
      int y;
      case Expose:
        if (event.xexpose.count == 0) {
          redraw();
        }
        break;
      case KeyPress:
        if (XLookupString(&event.xkey, text, 255, &key, 0) == 1) {
          // use the XLookupString routine to convert the invent
          // KeyPress data into regular text.  Weird but necessary...
          if ((text[0] == 'q') || (text[0] == 'Q')) {
            close_x();
          } else {
            // echo key press
            printf("You pressed the %c key!\n", text[0]);
          }
        }
        break;
      case ButtonPress:
        // get cursor position
        x = event.xbutton.x;
        y = event.xbutton.y;
        strcpy(text, "X is FUN!");
        XSetForeground(dis, gc, rand() % event.xbutton.x % 255);
        // draw text at cursor
        XDrawString(dis, win, gc, x, y, text, strlen(text));
        break;
      default:
        printf("Unhandled event.\n");
    }
{
          bool There_Is_Room = Is_There_Room_For_A_Char_In_Line(form);

          if (!(There_Is_Room ||
                ((Single_Line_Field(field) && Growable(field)))))
              return E_REQUEST_DENIED;

          if (!There_Is_Room && !Field_Grown(field,1))
            return E_SYSTEM_ERROR;

          winsch(form->w,(chtype)c);
        }
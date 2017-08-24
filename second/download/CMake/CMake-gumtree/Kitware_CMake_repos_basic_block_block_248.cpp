((--(form->currow))<0)
        {
          form->currow++;
          form->curcol++;
          return(E_REQUEST_DENIED);
        }
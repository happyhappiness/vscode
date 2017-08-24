{
      /* in this case fieldwin isn't derived from formwin, so we have
         to move the cursor in formwin by hand... */
      wmove(formwin,
            field->frow + form->currow - form->toprow,
            field->fcol + form->curcol - form->begincol);
      wcursyncup(formwin);
    }
copywin(form->w,
                        formwin,
                        first_modified_row,
                        0,
                        field->frow + first_modified_row - form->toprow,
                        field->fcol,
                        field->frow + first_unmodified_row - form->toprow - 1,
                        field->cols + field->fcol - 1,
                        0)
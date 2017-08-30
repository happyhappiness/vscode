    return;

    }



  height -= 5;

  m_Height = height;



  int size = m_Entries->size();

  bool isNewPage;

  for(int i=0; i < size; i++)

    {

    int row = (i % height) + 1;  

    int page = (i / height) + 1;

    isNewPage = ( page > 1 ) && ( row == 1 );



    (*m_Entries)[i]->m_Label->Move(left, top+row-1, isNewPage);

    (*m_Entries)[i]->m_IsNewLabel->Move(left+32, top+row-1, false);

    (*m_Entries)[i]->m_Entry->Move(left+33, top+row-1, false);

    }

  m_Form = new_form(m_Fields);

  post_form(m_Form);

  this->UpdateStatusBar();

  this->PrintKeys();

  touchwin(m_Window); 

  refresh();

}



void cmCursesMainForm::PrintKeys()

{

  int x,y;

  getmaxyx(m_Window, y, x);

  if ( x < cmCursesMainForm::MIN_WIDTH  || 

       y < cmCursesMainForm::MIN_HEIGHT )

    {

    return;

    }

  char firstLine[512], secondLine[512];

  sprintf(firstLine,  "C)onfigure             G)enerate and Exit");

  sprintf(secondLine, "Q)uit                  H)elp");



  curses_move(y-2,0);

  printw(firstLine);


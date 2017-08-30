    CurrentForm = this;

    this->Render(1,1,x,y);

    }



   

  this->InitializeUI();

  this->Render(1, 1, x, y);

  

  return 0;

}



void cmCursesMainForm::AddError(const char* message, const char*)

{

  m_Errors.push_back(message);


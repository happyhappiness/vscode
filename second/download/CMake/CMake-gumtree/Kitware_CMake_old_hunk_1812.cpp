 
}

void CMakeErrorHandler(const char* message, const char* title, bool&)
{
  cmCursesForm::CurrentForm->AddError(message, title);
}

int main(int argc, char** argv)

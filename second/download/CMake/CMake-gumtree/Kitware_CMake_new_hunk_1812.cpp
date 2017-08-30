 

}



void CMakeErrorHandler(const char* message, const char* title, bool&, void* clientData)

{

  cmCursesForm* self = static_cast<cmCursesForm*>( clientData );

  self->AddError(message, title);

}



int main(int argc, char** argv)


#include <iostream>
#include <string>
#include <vector>

#include "my_zip.h"


int main( int argc, char** argv )
{
     ZipManager zipManager;

     if ( !zipManager.createZipArchiveFromDirectory( "/home/andrey/Projects/testBoost/to/da.zip", "/home/andrey/Projects/testBoost/from" ) )
     {
          std::cout << "Error" << std::endl;
     }
     return 0;
}

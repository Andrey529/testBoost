
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/filesystem.hpp>

#include <memory>

#include <iostream>
#include "my_zip.h"

using namespace boost::filesystem;

ZipManager::~ZipManager()
{}


ZipManager::ZipManager() = default;


bool ZipManager::createZipArchiveFromDirectory( const std::string& zipArchiveFileName, const std::string& directoryName )
{
     int err;
     ZipArchiveWrapper zipArchive( zip_open( zipArchiveFileName.c_str(), ZIP_CREATE | ZIP_EXCL, &err ) );

     if ( zipArchive.isNull() )
     {
          zip_error_t error;
          zip_error_init_with_code( &error, err );
          std::cout << zip_error_strerror( &error );
          zip_error_fini( &error );
          return false;
     }

     std::cout << "Created empty archive" << std::endl;

     using namespace boost::filesystem;

     try
     {
          recursive_directory_iterator endItr;
          boost::filesystem::path dbFilePath( directoryName );
          for ( recursive_directory_iterator i( directoryName ); i != endItr; ++i )
          {
               // Игнорируем папки
               if ( !is_regular_file( i->status() ) )
               {
                    continue;
               }

               zip_error_t error;
               ZipSourceWrapper source( zip_source_file_create( i->path().native().c_str(), 0, -1, &error ) );
               
               if ( source.isNull() || zip_file_add( zipArchive.get(), i->path().native().c_str(), source.get(), ZIP_FL_ENC_UTF_8 ) < 0 )
               {
                    std::cout << "error adding file: " << zip_strerror( zipArchive.get() ) << std::endl;
               }
               std::cout << "Registered " << i->path().native().c_str() << " file" << std::endl;
          }

     }
     catch( const filesystem_error& ex )
     {
          std::cout << ex.what() << std::endl;
          return false;
     }
     return true;
}




// утечки
// bool ZipManager::createZipArchiveFromDirectory( const std::string& zipArchiveFileName, const std::string& directoryName )
// {
//      int err;
//      auto archiveDeleter = []( zip_t* p ){
//           zip_close( p );
//      };
//      Wrapper< zip_t*, decltype( archiveDeleter ) > zipArchive( zip_open( zipArchiveFileName.c_str(), ZIP_CREATE | ZIP_EXCL, &err ), archiveDeleter );

//      if ( zipArchive.isNull() )
//      {
//           zip_error_t error;
//           zip_error_init_with_code( &error, err );
//           std::cout << zip_error_strerror( &error );
//           zip_error_fini( &error );
//           return false;
//      }

//      std::cout << "Created empty archive" << std::endl;

//      using namespace boost::filesystem;

//      try
//      {
//           recursive_directory_iterator endItr;
//           boost::filesystem::path dbFilePath( directoryName );
//           for ( recursive_directory_iterator i( directoryName ); i != endItr; ++i )
//           {
//                // Игнорируем папки
//                if ( !is_regular_file( i->status() ) )
//                {
//                     continue;
//                }

//                zip_error_t error;
//                auto sourceDeleter = []( zip_source_t* p ){
//                     zip_source_free( p );
//                };
//                Wrapper< zip_source_t*, decltype( sourceDeleter ) > source( zip_source_file_create( i->path().native().c_str(), 0, -1, &error ), sourceDeleter );
               
//                if ( source.isNull() || zip_file_add( zipArchive.get(), i->path().native().c_str(), source.get(), ZIP_FL_ENC_UTF_8 ) < 0 )
//                {
//                     std::cout << "error adding file: " << zip_strerror( zipArchive.get() ) << std::endl;
//                }
//                std::cout << "Registered " << i->path().native().c_str() << " file" << std::endl;
//           }

//      }
//      catch( const filesystem_error& ex )
//      {
//           std::cout << ex.what() << std::endl;
//           return false;
//      }
//      return true;
// }





// bool ZipManager::createZipArchiveFromDirectory( const std::string& zipArchiveFileName, const std::string& directoryName )
// {
//      int err;
//      zip_t* zipArchive = zip_open( zipArchiveFileName.c_str(), ZIP_CREATE | ZIP_EXCL, &err );

//      if ( zipArchive == NULL )
//      {
//           zip_error_t error;
//           zip_error_init_with_code( &error, err );
//           std::cout << zip_error_strerror( &error );
//           zip_error_fini( &error );
//           return false;
//      }

//      using namespace boost::filesystem;

//      try
//      {
//           recursive_directory_iterator endItr;
//           boost::filesystem::path dbFilePath( directoryName );
//           for ( recursive_directory_iterator i( directoryName ); i != endItr; ++i )
//           {
//                // Игнорируем папки
//                if ( !is_regular_file( i->status() ) )
//                {
//                     continue;
//                }

//                zip_source_t* s;
//                zip_error_t error;
//                if ( ( s = zip_source_file_create( i->path().native().c_str(), 0, -1, &error ) ) == NULL ||
//                     zip_file_add( zipArchive, i->path().native().c_str(), s, ZIP_FL_ENC_UTF_8 ) < 0 )
//                {
//                     zip_source_free( s );
//                     std::cout << "error adding file: " << zip_strerror( zipArchive ) << std::endl;
//                }
//           }

//      }
//      catch( const filesystem_error& ex )
//      {
//           std::cout << ex.what() << std::endl;
//           zip_close( zipArchive );
//           return false;
//      }

//      zip_close( zipArchive );
//      return true;
// }



// bool ZipManager::createZipArchiveFromDirectory( const std::string& zipArchiveFileName, const std::string& directoryName )
// {
//      int err;

//      auto deleter = []( zip_t* p ){
//           zip_close( p );
//      };
//      std::shared_ptr< zip_t > zipArchive( zip_open( zipArchiveFileName.c_str(), ZIP_CREATE | ZIP_EXCL, &err ), deleter );

//      if ( !zipArchive )
//      {
//           zip_error_t error;
//           zip_error_init_with_code( &error, err );
//           std::cout << zip_error_strerror( &error );
//           zip_error_fini( &error );
//           return false;
//      }

//      std::cout << "Created empty archive" << std::endl;

//      using namespace boost::filesystem;

//      try
//      {
//           recursive_directory_iterator endItr;
//           boost::filesystem::path dbFilePath( directoryName );
//           for ( recursive_directory_iterator i( directoryName ); i != endItr; ++i )
//           {
//                // Игнорируем папки
//                if ( !is_regular_file( i->status() ) )
//                {
//                     continue;
//                }

//                zip_error_t error;
//                auto source_deleter = []( zip_source_t* p ){
//                     zip_source_free( p );
//                };
//                std::shared_ptr< zip_source_t > source( zip_source_file_create( i->path().native().c_str(), 0, -1, &error ), source_deleter );
               
//                if ( !source || zip_file_add( zipArchive.get(), i->path().native().c_str(), source.get(), ZIP_FL_ENC_UTF_8 ) < 0 )
//                {
//                     std::cout << "error adding file: " << zip_strerror( zipArchive.get() ) << std::endl;
//                }
//                std::cout << "Registered " << i->path().native().c_str() << " file" << std::endl;
//           }

//      }
//      catch( const filesystem_error& ex )
//      {
//           std::cout << ex.what() << std::endl;
//           return false;
//      }
//      return true;
// }

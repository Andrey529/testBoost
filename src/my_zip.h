#pragma once

#ifndef ZIP_H
#define ZIP_H

#include <string>
#include <set>
#include <zip.h>


// template < typename value_type, typename deleter_type >
// class Wrapper
// {
// public:
//      ~Wrapper() { deleter_( obj_ ); }

//      explicit Wrapper( value_type obj, deleter_type deleter )
//      : obj_( obj )
//      , deleter_( deleter )
//      {
//      }

//      Wrapper( const Wrapper& other ) = delete;
//      Wrapper& operator=( const Wrapper& other ) = delete;
//      Wrapper( Wrapper&& other ) = delete;
//      Wrapper&& operator=( Wrapper&& other ) = delete;

//      bool isNull() const { return obj_ == NULL; }

//      value_type& get() { return obj_; }

// private:
//      value_type obj_;
//      deleter_type deleter_;
// };


class ZipSourceWrapper
{
public:
     
     ~ZipSourceWrapper() { zip_source_free( source_ ); }

     explicit ZipSourceWrapper( zip_source_t* source ) : source_( source ) { }

     bool isNull() const { return source_ == NULL; }

     zip_source_t* get() { return source_; }

private:
     zip_source_t* source_;
};


class ZipArchiveWrapper
{
public:
     
     ~ZipArchiveWrapper() { zip_close( archive_ ); }

     explicit ZipArchiveWrapper( zip_t* archive ) : archive_( archive ) { }

     bool isNull() const { return archive_ == NULL; }

     zip_t* get() { return archive_; }

private:
     zip_t* archive_;
};


/// @brief Класс для работы с zip-архивами
class ZipManager
{
public:
     typedef std::set< std::string > FilesList;
     static const int DefaultCompressionLevel; 

public:
     /// @brief Дуструктор класса
     virtual ~ZipManager();
     
     /// @brief Конструктор класса
     explicit ZipManager();

     bool createZipArchiveFromDirectory( const std::string& zipArchiveFileName, const std::string& directoryName );
};


#endif
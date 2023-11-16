#include <boost/filesystem.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <fstream>
#include <iostream>

int main( int argc, char** argv )
{

     // Read filename from the first command line argument
     // boost::iostreams::file_sink ofile( "../to/compressedData.tar.gz" );

     // boost::iostreams::filtering_streambuf< boost::iostreams::output > outbuf;
     // outbuf.set_auto_close( true );

     // outbuf.push( boost::iostreams::gzip_compressor( boost::iostreams::gzip_params( 9 ) ) );
     // outbuf.push( ofile );

     // std::string compressedDirPathStr( "../from" );
     // std::string archiveName( "../to/archive.tar" );

     // std::string command( "tar -czvf " + archiveName + " " + compressedDirPathStr + " .clang-format" );

     // std::system( command.c_str() );

     // std::ifstream ifs( archiveName, std::ios::binary );

     // boost::iostreams::copy( ifs, outbuf );

     // // Cleanup
     // boost::iostreams::close( outbuf ); // Don't forget this!
     // ofile.close();

     // Read filename from the first command line argument
     // std::string archiveName( "../to/archive.tar" );

     // std::string compressedDirPathStr( "../from" );
     // std::string command( "tar -cvf " + archiveName + " " + compressedDirPathStr + " ../.clang-format" );
     // std::system( command.c_str() );

     // archiveName += ".gz";
     // std::ofstream file( archiveName, std::ios_base::out | std::ios_base::binary );
     // boost::iostreams::filtering_streambuf< boost::iostreams::output > outbuf;
     // outbuf.push( boost::iostreams::gzip_compressor( boost::iostreams::gzip_params( 9 ) ) );
     // outbuf.push( file );
     // // Convert streambuf to ostream
     // std::ostream out( &outbuf );
     // // Write some test data

     // std::ifstream ifs( "../from/file3.txt", std::ios::binary );
     // // Write some test data

     // boost::iostreams::copy( ifs, outbuf );

     // boost::iostreams::close( outbuf ); // Don't forget this!
     // file.close();

     using namespace std;

     ofstream file( argv[ 1 ], ios_base::out | ios_base::binary );
     boost::iostreams::filtering_streambuf< boost::iostreams::output > outbuf;
     outbuf.push( boost::iostreams::gzip_compressor( boost::iostreams::gzip_params( 9 ) ) );
     outbuf.push( file );
     // Convert streambuf to ostream
     ostream out( &outbuf );
     // Write some test data
     out << "This is a test text!\n";
     // Cleanup
     boost::iostreams::close( outbuf ); // Don't forget this!
     file.close();
}
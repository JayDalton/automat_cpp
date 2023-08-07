#pragma once

#include "common.hpp"

// #include <boost/archive/iterators/base64_from_binary.hpp>
// #include <boost/archive/iterators/insert_linebreaks.hpp>
// #include <boost/archive/iterators/ostream_iterator.hpp>
// #include <boost/archive/iterators/transform_width.hpp>
#include <boost/beast/core/detail/base64.hpp>

#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include <iostream>
#include <fstream>
#include <vector>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

namespace Example09
{

// inline auto encodeBase64(const std::string& input) -> std::string
// {
//     using namespace boost::archive::iterators;

//     // convert binary values to base64 characters
//     // retrieve 6 bit integers from a sequence of 8 bit bytes
//     // compose all the above operations in to a new iterator
//     using base64_text = base64_from_binary<transform_width<const char*, 8, 8>>;

//     std::stringstream os;

//     std::copy(
//         base64_text(input.c_str()),
//         base64_text(input.c_str() + input.size()),
//         ostream_iterator<char>(os));

//     return os.str();
// }

// inline auto decodeBase64(const std::string& base64Data) -> std::string
// {
//     try {
//         using namespace boost::beast::detail;

//         std::string result;
//         result.resize(base64::decoded_size(base64Data.size()));

//         const auto size{base64::decode(&result.front(), base64Data.c_str(), base64Data.size())};

//         result.resize(size.first);
//         return result;
//     } catch (...) {
//         return {};
//     }
// }

using byte = unsigned char;

struct Base64Encode
{
    const unsigned m1 = 63 << 18, m2 = 63 << 12, m3 = 63 << 6;

    std::string encode( std::vector<byte> v )
    {
        std::string res;
        unsigned d, a = 0, l = static_cast<unsigned>( v.size() );

        while( l > 2 )
        {
            d = v[a++] << 16 | v[a++] << 8 | v[a++];	
            res.append( 1, char_set.at( ( d & m1 ) >> 18 ) );	
            res.append( 1, char_set.at( ( d & m2 ) >> 12 ) );	
            res.append( 1, char_set.at( ( d & m3 ) >>  6 ) );
            res.append( 1, char_set.at( d & 63 ) );
            l -= 3;
        }
        if( l == 2 )
        {
            d = v[a++] << 16 | v[a++] << 8;
            res.append( 1, char_set.at( ( d & m1 ) >> 18 ) );	
            res.append( 1, char_set.at( ( d & m2 ) >> 12 ) );	
            res.append( 1, char_set.at( ( d & m3 ) >>  6 ) );
            res.append( 1, '=' );
        }
        else if( l == 1 )
        {
            d = v[a++] << 16;
            res.append( 1, char_set.at( ( d & m1 ) >> 18 ) );	
            res.append( 1, char_set.at( ( d & m2 ) >> 12 ) );	
            res.append( "==", 2 );
        }
        return res;
    }

private:
    std::string char_set{"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"};
};

// ################################################################################################


typedef unsigned char ubyte;
const auto BASE64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

std::vector<ubyte> encode(const std::vector<ubyte>& source) {
    auto it = source.cbegin();
    auto end = source.cend();

    std::vector<ubyte> sink;
    while (it != end) {
        auto b1 = *it++;
        int acc;

        sink.push_back(BASE64[b1 >> 2]);            // first output (first six bits from b1)

        acc = (b1 & 0x3) << 4;                      // last two bits from b1
        if (it != end) {
            auto b2 = *it++;
            acc |= (b2 >> 4);                       // first four bits from b2

            sink.push_back(BASE64[acc]);            // second output

            acc = (b2 & 0xF) << 2;                  // last four bits from b2
            if (it != end) {
                auto b3 = *it++;
                acc |= (b3 >> 6);                   // first two bits from b3

                sink.push_back(BASE64[acc]);        // third output
                sink.push_back(BASE64[b3 & 0x3F]);  // fouth output (final six bits from b3)
            } else {
                sink.push_back(BASE64[acc]);        // third output
                sink.push_back('=');                // fourth output (1 byte padding)
            }
        } else {
            sink.push_back(BASE64[acc]);            // second output
            sink.push_back('=');                    // third output (first padding byte)
            sink.push_back('=');                    // fourth output (second padding byte)
        }
    }
    return sink;
}

int findIndex(ubyte val) {
    if ('A' <= val && val <= 'Z') {
        return val - 'A';
    }
    if ('a' <= val && val <= 'z') {
        return val - 'a' + 26;
    }
    if ('0' <= val && val <= '9') {
        return val - '0' + 52;
    }
    if ('+' == val) {
        return 62;
    }
    if ('/' == val) {
        return 63;
    }
    return -1;
}

std::vector<ubyte> decode(const std::vector<ubyte>& source) {
    if (source.size() % 4 != 0) {
        throw new std::runtime_error("Error in size to the decode method");
    }

    auto it = source.cbegin();
    auto end = source.cend();

    std::vector<ubyte> sink;
    while (it != end) {
        auto b1 = *it++;
        auto b2 = *it++;
        auto b3 = *it++; // might be first padding byte
        auto b4 = *it++; // might be first or second padding byte

        auto i1 = findIndex(b1);
        auto i2 = findIndex(b2);
        auto acc = i1 << 2;     // six bits came from the first byte
        acc |= i2 >> 4;         // two bits came from the first byte

        sink.push_back(acc);    // output the first byte

        if (b3 != '=') {
            auto i3 = findIndex(b3);

            acc = (i2 & 0xF) << 4;  // four bits came from the second byte
            acc |= i3 >> 2;         // four bits came from the second byte

            sink.push_back(acc);    // output the second byte

            if (b4 != '=') {
                auto i4 = findIndex(b4);

                acc = (i3 & 0x3) << 6;  // two bits came from the third byte
                acc |= i4;              // six bits came from the third byte

                sink.push_back(acc);    // output the third byte
            }
        }
    }
    return sink;
}


int main( int argc, char* argv[] )
{
    Base64Encode b;
    std::basic_ifstream<byte> f( "favicon.ico", std::ios::binary );
    std::string r = b.encode( std::vector<byte>( ( std::istreambuf_iterator<byte>( f ) ), std::istreambuf_iterator<byte>() ) );
    std::copy( r.begin(), r.end(), std::ostream_iterator<char>( std::cout ) );


    std::string data = "VG8gZXJyIGlzIGh1bWFuLCBidXQgdG8gcmVhbGx5IGZvdWwgdGhpbmdzIHVwIHlvdSBuZWVkIGEgY29tcHV0ZXIuCiAgICAtLVBhdWwgUi5FaHJsaWNo";
    std::vector<ubyte> datav{ std::begin(data), std::end(data) };
    std::cout << data << "\n\n" << decode(datav).data() << std::endl;

}

// int main()
// {
//     constexpr auto data{
//         "Lorem ipsum dolor sit amet, consectetur adipiscing elit. "
//         "Fusce ornare ullamcorper ipsum ac gravida."
//     };

//     const base64 = encodeBase64(data);
//     const test = decodeBase64(base64);

//     print("original: {}\n\n", data);
//     print("base64: {}\n\n", base64);
//     print("test: {}\n\n", test);    

//     assert(data == test);

//     return 0;
// }

}
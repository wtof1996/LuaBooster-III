#ifndef IO_HPP_INCLUDED
#define IO_HPP_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <boost/gil/extension/io/png_dynamic_io.hpp>
#include <boost/gil/extension/io/jpeg_dynamic_io.hpp>
#include <boost/gil/extension/numeric/sampler.hpp>
#include <boost/gil/extension/numeric/resample.hpp>
#include <boost/filesystem/operations.hpp>

namespace io{
    using std::cout;
    using std::cerr;
    using std::endl;
    using std::vector;
    using std::string;
    using std::bitset;

    using MyString = std::string;
    using MySize = std::pair<unsigned int, unsigned int>;
    using MyByte = std::pair<unsigned char, unsigned char>;

    typedef boost::mpl::vector<
            boost::gil::rgb8_image_t,
            boost::gil::rgba8_image_t
    > img_types;

    template<typename T>
    void notice(const T &i) { cout << i << endl;}
    template<typename T>
    void notice(const T &&i) { cout << i << endl;}

    template<typename T>
    void log(const T &i) { cerr << i << endl;}
    template<typename T>
    void log(const T &&i) { cerr << i << endl;}

    MyByte RGB888_to_RGB555(const unsigned char r, const unsigned char g, const unsigned char b);

    struct getRGB
    {
        typedef void result_type; // required
        template <class View>
        void operator()(const View& src) const {
            boost::gil::gil_function_requires<boost::gil::ImageViewConcept<View>>();

            auto w = src.width(), h = src.height();

            for(decltype(w) y = 0; y < h; ++y){
                for(decltype(h) x = 0; x < w; ++x){

                }
            }

        }

    };

    class Image
    {
    public:
        void readImage();
        void convert();
        const vector<MyByte>& getData() { return data;}

    private:
        boost::gil::any_image<img_types> src;
        vector<MyByte> data;
    };


};

#endif // IO_HPP_INCLUDED

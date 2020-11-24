#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <iostream>
#include <string>
#include <cmath>
#include <header.hpp>
#include <SFML/Graphics.hpp>

int main()
{
    std::string outText;
    tesseract::TessBaseAPI* api = new tesseract::TessBaseAPI();
    if (api->Init("C:\\src\\vcpkg\\buildtrees\\tesseract\\src\\4.1.1-1402ed03b0.clean\\tessdata", "eng")) {
        std::cerr << "Could not initialize tesseract." << std::endl;
        return 1;
    }
    Pix* image = pixRead("D:\\Github\\date2.png");
    api->SetImage(image);
    outText = api->GetUTF8Text();
    api->End();
    std::string x, y;
    x = outText.substr(0, outText.find('\n'));
    y = outText.substr(x.length() + 1, outText.find('\n', x.length() + 1) - 1);
    std::cout << outText << std::endl << std::endl;
    std::cout << "that is x "  << x << std::endl << std::endl;
    std::cout << "that is y " << y << std::endl << std::endl;
    pixDestroy(&image);

    function_plot_drawer object;
    object.main_cicle(x, y);
    return 0; 
}

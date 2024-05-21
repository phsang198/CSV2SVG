#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

struct SvgInfo {
    std::string filename;
    std::string text;
    std::string font;
    std::string color;
    std::string justify;
    int font_size;
};

void writeSvg(const SvgInfo& info) {
    std::ofstream svgFile(info.filename + ".svg");

    if (svgFile.is_open()) {
        svgFile << "<svg>\n";
        svgFile << "  <text font-family=\"" << info.font << "\" fill=\"" << info.color << "\" ";

        if (info.justify == "left") {
            svgFile << "text-anchor=\"start\" ";
        }
        else if (info.justify == "middle") {
            svgFile << "text-anchor=\"middle\" ";
        }
        else if (info.justify == "end") {
            svgFile << "text-anchor=\"end\" ";
        }

        svgFile << "font-size=\"" << info.font_size << "\">" << info.text << "</text>\n";
        svgFile << "</svg>\n";

        svgFile.close();

        std::cout << "SVG file \"" << info.filename << ".svg\" created successfully.\n";
    }
    else {
        std::cerr << "Unable to create SVG file for " << info.filename << "\n";
    }
}

int main() {
    // Read CSV file
    std::ifstream csvFile("F:\\OutSource\\C++\\CSVConvert\\Book1.csv");
    if (!csvFile.is_open()) {
        std::cerr << "Unable to open CSV file.\n";
        return 1;
    }

    std::vector<SvgInfo> svgInfos;

    std::string line;
    while (std::getline(csvFile, line)) {
        std::stringstream ss(line);
        SvgInfo info;
        std::getline(ss, info.filename, ',');
        std::getline(ss, info.text, ',');
        std::getline(ss, info.font, ',');
        std::getline(ss, info.color, ',');
        std::getline(ss, info.justify, ',');
        ss >> info.font_size;

        svgInfos.push_back(info);
    }

    csvFile.close();

    // Generate SVG files
    for (const auto& info : svgInfos) {
        writeSvg(info);
    }

    return 0;
}
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <assert.h>

namespace TelCoColorCoder {

    enum MajorColor { WHITE, RED, BLACK, YELLOW, VIOLET };
    enum MinorColor { BLUE, ORANGE, GREEN, BROWN, SLATE };

    const char* MajorColorNames[] = { "White", "Red", "Black", "Yellow", "Violet" };
    const int numberOfMajorColors = sizeof(MajorColorNames) / sizeof(MajorColorNames[0]);

    const char* MinorColorNames[] = { "Blue", "Orange", "Green", "Brown", "Slate" };
    const int numberOfMinorColors = sizeof(MinorColorNames) / sizeof(MinorColorNames[0]);

    class ColorPair {
    private:
        MajorColor majorColor;
        MinorColor minorColor;
    public:
        ColorPair(MajorColor major, MinorColor minor) :
            majorColor(major), minorColor(minor) {}
        MajorColor getMajor() const { return majorColor; }
        MinorColor getMinor() const { return minorColor; }
        std::string ToString() const {
            return std::string(MajorColorNames[majorColor]) + " " + MinorColorNames[minorColor];
        }
    };

    ColorPair GetColorFromPairNumber(int pairNumber) {
        int zeroBased = pairNumber - 1;
        MajorColor major = (MajorColor)(zeroBased / numberOfMinorColors);
        MinorColor minor = (MinorColor)(zeroBased % numberOfMinorColors);
        return ColorPair(major, minor);
    }

    int GetPairNumberFromColor(MajorColor major, MinorColor minor) {
        return major * numberOfMinorColors + minor + 1;
    }

    std::vector<ColorPair> GetAllColorPairs() {
        std::vector<ColorPair> map;
        for (int major = 0; major < numberOfMajorColors; ++major) {
            for (int minor = 0; minor < numberOfMinorColors; ++minor) {
                map.emplace_back((MajorColor)major, (MinorColor)minor);
            }
        }
        return map;
    }

    // --- New Feature 1: Reference Manual ---
    std::string FormatReferenceManual() {
        auto pairs = GetAllColorPairs();
        std::ostringstream oss;
        for (size_t i = 0; i < pairs.size(); ++i) {
            oss << (i + 1) << " | " << pairs[i].ToString() << "\n";
        }
        return oss.str();
    }

    // --- New Feature 2: CSV Report ---
    std::string FormatCsvReport() {
        auto pairs = GetAllColorPairs();
        std::ostringstream oss;
        oss << "PairNumber,MajorColor,MinorColor\n";
        for (size_t i = 0; i < pairs.size(); ++i) {
            oss << (i + 1) << ","
                << MajorColorNames[pairs[i].getMajor()] << ","
                << MinorColorNames[pairs[i].getMinor()] << "\n";
        }
        return oss.str();
    }
}

// --- Strong Tests ---
void testNumberToPair(int pairNumber,
    TelCoColorCoder::MajorColor expectedMajor,
    TelCoColorCoder::MinorColor expectedMinor)
{
    TelCoColorCoder::ColorPair colorPair = TelCoColorCoder::GetColorFromPairNumber(pairNumber);
    assert(colorPair.getMajor() == expectedMajor);
    assert(colorPair.getMinor() == expectedMinor);
}

void testPairToNumber(
    TelCoColorCoder::MajorColor major,
    TelCoColorCoder::MinorColor minor,
    int expectedPairNumber)
{
    int pairNumber = TelCoColorCoder::GetPairNumberFromColor(major, minor);
    assert(pairNumber == expectedPairNumber);
}

void testReferenceManual() {
    std::string manual = TelCoColorCoder::FormatReferenceManual();
    // strong checks
    assert(manual.find("1 | White Blue") != std::string::npos);
    assert(manual.find("25 | Violet Slate") != std::string::npos);
}

void testCsvReport() {
    std::string csv = TelCoColorCoder::FormatCsvReport();
    // strong checks
    assert(csv.find("PairNumber,MajorColor,MinorColor") != std::string::npos);
    assert(csv.find("1,White,Blue") != std::string::npos);
    assert(csv.find("25,Violet,Slate") != std::string::npos);
}

int main() {
    testNumberToPair(4, TelCoColorCoder::WHITE, TelCoColorCoder::BROWN);
    testNumberToPair(5, TelCoColorCoder::WHITE, TelCoColorCoder::SLATE);

    testPairToNumber(TelCoColorCoder::BLACK, TelCoColorCoder::ORANGE, 12);
    testPairToNumber(TelCoColorCoder::VIOLET, TelCoColorCoder::SLATE, 25);

    testReferenceManual();
    testCsvReport();

    std::cout << "All tests passed!\n";
    std::cout << "--- Reference Manual ---\n" 
              << TelCoColorCoder::FormatReferenceManual() << "\n";
    std::cout << "--- CSV Report ---\n"
              << TelCoColorCoder::FormatCsvReport() << "\n";

    return 0;
}

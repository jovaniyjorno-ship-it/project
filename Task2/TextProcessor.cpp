#include "pch.h"
#include "TextProcessor.h"
#include <locale>
#include <cctype>

// Сформировать частотный словарь слов
map<string, double> TextProcessor::makeWordsFrequencyDict(const string& fileName) {
    map<string, double> freqDict;

    fstream fs(fileName, ios::in);
    if (!fs.is_open()) {
        throw exception(("TextProcessor: Ошибка открытия файла " + fileName + " для чтения").c_str());
    }
    fs.imbue(locale(".1251"));

    int wordsCounter = 0;
    while (!fs.eof()) {
        string line;
        getline(fs, line);
        if (line.empty()) continue;

        vector<string> words = splitBySpace(line);
        for (const auto& word : words) {
            freqDict[word] += 1;
        }
        wordsCounter += words.size();

        fs.peek();
    }
    fs.close();

    for (auto& item : freqDict) {
        item.second /= wordsCounter;
    }
    return freqDict;
}

map<string, double> TextProcessor::makeLettersFrequencyDict(const string& fileName) {
    map<string, double> freqDict;

    fstream fs(fileName, ios::in);
    if (!fs.is_open()) {
        throw exception(("TextProcessor: Ошибка открытия файла " + fileName + " для чтения").c_str());
    }
    fs.imbue(locale(".1251"));

    string text;
    string line;
    while (getline(fs, line)) {
        text += line;
    }
    fs.close();

    int lettersCounter = 0;
    for (char c : text) {
        if (isalpha(static_cast<unsigned char>(c))) {
            char lowerC = tolower(static_cast<unsigned char>(c));
            freqDict[string(1, lowerC)] += 1;
            lettersCounter++;
        }
    }

    for (auto& item : freqDict) {
        item.second /= lettersCounter;
    }
    return freqDict;
}

// splitBySpace
vector<string> TextProcessor::splitBySpace(const string& line) {
    vector<string> words;
    stringstream ss(line);
    while (!ss.fail()) {
        string word;
        ss >> word;
        if (word.empty()) continue;
        words.emplace_back(word);
    }
    return words;
}
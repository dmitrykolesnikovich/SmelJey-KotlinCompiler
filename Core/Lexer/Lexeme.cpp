#include "Lexeme.h"
#include <utility>
#include <sstream>
#include <regex>

Lexeme::Lexeme() : Lexeme(0, 0, "", LexemeType::Error) {};

Lexeme::Lexeme(int col, int row, std::string text, LexemeType lexemeType, std::string errorDescription)
    : myColumn(col), myRow(row), myText(std::move(text)), myError(std::move(errorDescription)), myType(lexemeType) {}

std::ostream& operator<<(std::ostream& out, const Lexeme& lexeme) {
    out << lexeme.ToString();
    return out;
}

int Lexeme::GetColumn() const {
    return myColumn;
}

int Lexeme::GetRow() const {
    return myRow;
}

const std::string& Lexeme::GetText() const {
    return myText;
}

const std::string& Lexeme::GetError() const {
    return myError;
}

Lexeme::LexemeType Lexeme::GetType() const {
    return myType;
}

std::string Lexeme::ToString() const {
    std::stringstream ss;
    std::string textWithoutNewlines = std::regex_replace(myText, std::regex("\n"), "\\n");
    textWithoutNewlines = std::regex_replace(textWithoutNewlines, std::regex("\t"), "\\t");
    ss << myRow << "\t" << myColumn << "\t" << GetStringType() <<  (myError.empty() ? "" : "\t") << myError << "\t|" << textWithoutNewlines;
    return ss.str();
}

std::string Lexeme::LexemeToStr[]{ "EOF", "Word", "Key", "Num", "Op", "Br", "Str", "RStr", "StrRf", "RStrRf", "StrExp", "RStrExp", "Error", "Ignored" };

//std::unordered_map<std::string, Lexeme::LexemeType> Lexeme::StrToLexeme {
//    {"EOF", LexemeType::EndOfFile},
//    {"Word", LexemeType::Identifier },
//    {"" }
//};

std::string Lexeme::GetStringType() const {
    return LexemeToStr[(int)myType];
}

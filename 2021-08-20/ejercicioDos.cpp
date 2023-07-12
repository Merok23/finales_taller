#include <string>
#include <cctype>

void camelCase(std::string &unString) {
    char c = unString[0];
    c = toupper(c);
    unString[0] = c;
    for (int i = 1; i < unString.length(); i++) {
        c = unString[i];
        c = tolower(c);
        unString[i] = c;
    }
} 

void qtEditToCamel(QLineEdit& edit) {
    std::string camelText = edit.toText().toStdString();
    std::stringstream iss(camelText);
    std::string finalString = "";
    std::string word;
    while (iss >> word) {
        camelCase(word);
        finalString += word;
    }
    edit.setText(finalString);
}
/*************************************
* Автор:   Кучина Мария              *
* Задание: Строки, векторы и словари *
* Вариант: 10                        *
**************************************/
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <limits>
#include <cctype>

using namespace std;

int main() {
  int maxStringLength = 200;
  int maxVectorSize = 100;
  int minValueLimit = -1000;
  int maxValueLimit = 1000;
  int maxRecordCount = 100;
  int maxFieldLength = 200;
  int asciiLimit = 127;
  int maxKeyLength = 40;

  char partLetter;
  cout << "Enter part letter (A, B, C, D): ";
  if (!(cin >> partLetter)) {
      return 1;
  }

  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  if (partLetter == 'A' || partLetter == 'a') {
      cout << "Enter string: ";
      string inputLine;
      if (!getline(cin, inputLine)) {
          cout << "INVALID\n";
          return 1;
      }

      if (inputLine.length() > maxStringLength) {
          cout << "INVALID\n";
          return 1;
      }

      string resultString;

      for (size_t symbolIndex = 0; symbolIndex < inputLine.length(); ++symbolIndex) {
          char currentSymbol = inputLine[symbolIndex];

          if (static_cast<unsigned char>(currentSymbol) > asciiLimit) {
              cout << "INVALID\n";
              return 1;
          }

          resultString += static_cast<char>(tolower(static_cast<unsigned char>(currentSymbol)));
      }

      cout << resultString << "\n";
  }
  else if (partLetter == 'B' || partLetter == 'b') {
      cout << "Enter count of elements: ";
      int vectorSize;
      if (!(cin >> vectorSize) || vectorSize < 0 || vectorSize > maxVectorSize) {
          cout << "INVALID\n";
          return 1;
      }

      cout << "Enter elements: ";
      vector<int> numbers;
      int currentNumber;

      for (int elementIndex = 0; elementIndex < vectorSize; ++elementIndex) {
          if (!(cin >> currentNumber) || currentNumber < minValueLimit || currentNumber > maxValueLimit) {
            cout << "INVALID\n";
            return 1;
          }
          numbers.push_back(currentNumber);
      }

      if (numbers.empty()) {
          cout << "EMPTY\n";
          return 0;
      }

      for (int leftIndex = 0, rightIndex = static_cast<int>(numbers.size()) - 1; leftIndex < rightIndex; ++leftIndex, --rightIndex) {
          int temporaryValue = numbers[leftIndex];
          numbers[leftIndex] = numbers[rightIndex];
          numbers[rightIndex] = temporaryValue;
      }

      for (size_t elementIndex = 0; elementIndex < numbers.size(); ++elementIndex) {
          if (elementIndex > 0) {
              cout << " ";
          }
          cout << numbers[elementIndex];
      }
      cout << "\n";
  }
  else if (partLetter == 'C' || partLetter == 'c') {
      cout << "Enter count of pairs: ";
      int pairCount;
      if (!(cin >> pairCount) || pairCount < 0 || pairCount > maxRecordCount) {
          cout << "INVALID\n";
          return 1;
      }

      cin.ignore(numeric_limits<streamsize>::max(), '\n');

      map<string, int> dataDictionary;
      string currentKey;
      int currentValue;

      cout << "Enter pairs (key value): \n";
      for (int pairIndex = 0; pairIndex < pairCount; ++pairIndex) {
          if (!(cin >> currentKey >> currentValue)) {
              cout << "INVALID\n";
              return 1;
          }

          if (currentKey.empty() || currentKey.length() > maxKeyLength) {
              cout << "INVALID\n";
              return 1;
          }

          for (size_t symbolIndex = 0; symbolIndex < currentKey.length(); ++symbolIndex) {
              if (static_cast<unsigned char>(currentKey[symbolIndex]) > asciiLimit || currentKey[symbolIndex] == ' ') {
                  cout << "INVALID\n";
                  return 1;
              }
          }

          if (currentValue < minValueLimit || currentValue > maxValueLimit) {
              cout << "INVALID\n";
              return 1;
          }

          dataDictionary[currentKey] = currentValue;
      }

      cout << "Enter query key and increment: ";
      string queryKey;
      int incrementValue;

      if (!(cin >> queryKey >> incrementValue) || incrementValue < minValueLimit || incrementValue > maxValueLimit) {
          cout << "INVALID\n";
          return 1;
      }

      auto foundEntry = dataDictionary.find(queryKey);
      if (foundEntry != dataDictionary.end()) {
          foundEntry->second += incrementValue;
      }
      else {
          dataDictionary[queryKey] = incrementValue;
      }

      if (dataDictionary.empty()) {
          cout << "EMPTY\n";
      }
      else {
          for (const pair<const string, int>& entry : dataDictionary) {
              cout << entry.first << " " << entry.second << "\n";
           }
      }
  }
  else if (partLetter == 'D' || partLetter == 'd') {
      cout << "Enter count of records: ";
      int recordCount;
      if (!(cin >> recordCount) || recordCount < 0 || recordCount > maxRecordCount) {
          cout << "INVALID\n";
          return 1;
      }

      cin.ignore(numeric_limits<streamsize>::max(), '\n');

      vector<map<string, string>> addressBook;
      bool isValidInput = true;

      cout << "Enter records (name and email): \n";
      for (int recordIndex = 0; recordIndex < recordCount; ++recordIndex) {
          string personName;
          string personEmail;

          if (!getline(cin, personName) || !getline(cin, personEmail)) {
              isValidInput = false;
              break;
          }

          if (personName.length() < 1 || personName.length() > maxFieldLength ||
              personEmail.length() < 1 || personEmail.length() > maxFieldLength) {
              isValidInput = false;
              break;
          }

          if (personName.front() == ' ' || personName.back() == ' ' ||
              personEmail.front() == ' ' || personEmail.back() == ' ') {
              isValidInput = false;
              break;
          }

          for (size_t symbolIndex = 0; symbolIndex < personName.length(); ++symbolIndex) {
              if (static_cast<unsigned char>(personName[symbolIndex]) > asciiLimit) {
                  isValidInput = false;
                  break;
              }
          }

          if (!isValidInput) {
              break;
          }

          for (size_t symbolIndex = 0; symbolIndex < personEmail.length(); ++symbolIndex) {
              if (static_cast<unsigned char>(personEmail[symbolIndex]) > asciiLimit) {
                  isValidInput = false;
                  break;
              }
          }

          if (!isValidInput) {
              break;
          }

          map<string, string> currentRecord;
          currentRecord["name"] = personName;
          currentRecord["email"] = personEmail;
          addressBook.push_back(currentRecord);
      }

      if (!isValidInput) {
          cout << "INVALID\n";
          return 1;
      }

      vector<string> invalidEmailOwners;

      for (size_t bookIndex = 0; bookIndex < addressBook.size(); ++bookIndex) {
          const map<string, string>& currentPerson = addressBook[bookIndex];
          string email = currentPerson.at("email");

          bool hasSpaces = false;

          for (size_t symbolIndex = 0; symbolIndex < email.length(); ++symbolIndex) {
              if (email[symbolIndex] == ' ') {
                  hasSpaces = true;
                  break;
              }
          }

          int atSymbolCount = 0;
          size_t atSymbolPosition = string::npos;

          for (size_t symbolIndex = 0; symbolIndex < email.length(); ++symbolIndex) {
              if (email[symbolIndex] == '@') {
                  ++atSymbolCount;
                  if (atSymbolPosition == string::npos) {
                      atSymbolPosition = symbolIndex;
                  }
              }
          }

          bool isValidEmail = true;

          if (hasSpaces) {
              isValidEmail = false;
          }

          if (atSymbolCount != 1) {
              isValidEmail = false;
          }

          if (atSymbolPosition == 0 || atSymbolPosition == email.length() - 1) {
              isValidEmail = false;
          }

          if (!isValidEmail) {
              invalidEmailOwners.push_back(currentPerson.at("name"));
          }
      }

      if (invalidEmailOwners.empty()) {
          cout << "EMPTY\n";
      }
      else {
          for (size_t resultIndex = 0; resultIndex < invalidEmailOwners.size(); ++resultIndex) {
              cout << invalidEmailOwners[resultIndex] << "\n";
          }
      }
  }
  else {
      cout << "INVALID\n";
  }

  return 0;
}
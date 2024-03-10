//////////////////////////////////////////////////////////////////////////////////////////////////
// Name:        encrypt.hpp
// Description: Series of functions to encrypt strings.
// Author:      Matheus Diniz Abrao, <mabrao99@outlook.com>
// Modified by:
// Created:     Feb/2024
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef ENCRYPT_HPP
#define ENCRYPT_HPP

#include <iostream>
#include <algorithm>
#include <string>
#include <map>

class Encrypt {
public:

    enum EncryptionLevel {
        eLevel1,
        eLevel2,
        eLevel3,
        eLevel4,
        eLevel5
    };

    static EncryptionLevel getLevelFromStr(std::string str) {
        static const std::map<std::string, EncryptionLevel> strLevelMap = {
        {"Level 1", EncryptionLevel::eLevel1},
        {"Level 2", EncryptionLevel::eLevel2},
        {"Level 3", EncryptionLevel::eLevel3},
        {"Level 4", EncryptionLevel::eLevel4},
        {"Level 5", EncryptionLevel::eLevel5}
        // Add more mappings as needed
        };

        auto it = strLevelMap.find(str);
        if (it != strLevelMap.end()) {
            return it->second;
        } else {
            // Handle the case when the string does not match any enumeration constant
            throw std::invalid_argument("Invalid string for EncryptionLevel enum");
        }
    }


    static std::string encryptString(const std::string str_level, std::string& string) {
        EncryptionLevel level = getLevelFromStr(str_level);
        std::string result = "";
        switch (level) {
            case eLevel1:
                return caesarCipher(string, 5);
            case eLevel2:
                return "";
            case eLevel3:
                return "";
            case eLevel4:
                return "";
            case eLevel5:
                return "";
            default:
                return "";
        }
    }

    static std::string decryptString(const std::string str_level, std::string& string) {
        EncryptionLevel level = getLevelFromStr(str_level);
        std::string result = "";
        switch (level) {
            case eLevel1:
                return caesarCipher(string, 5, true);
            case eLevel2:
                return "";
            case eLevel3:
                return "";
            case eLevel4:
                return "";
            case eLevel5:
                return "";
            default:
                return "";
        }
    }

    // simple caesar cipher algorithm that returns true on success
    static std::string caesarCipher(std::string& string, int shift = 5, bool decrypt = false) {
        bool done = false;
        for (char& c : string) {
            if (std::isalpha(c)) {
                char base = (std::isupper(c)) ? 'A' : 'a';
                if (decrypt) {
                    // Decryption: Apply reverse shift
                    c = static_cast<char>((c - base - shift + 26) % 26 + base);
                } else {
                    // Encryption: Apply shift
                    c = static_cast<char>((c - base + shift) % 26 + base);
                }
                done = true;

            }
        }

        if (done) {
            return string;
        } else {
            return "";
        }

    }
};

#endif // DECRYPT_HPP
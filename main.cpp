#include<vector>
#include<string>
#include<iostream>
#include<bitset>
#include <cstdint>

using namespace std;

class Codec {
public:
    Codec() {};
    ~Codec() {};

    string encode(const vector<string>& strs) {
        string encoded_str{};
        encoded_str.reserve(sizeof(strs) + strs.size());
        string current_str{};
        char encrypted_char{};

        for(size_t i{0}; i < strs.size(); i++) {
            current_str = strs[i];
            if(current_str.empty()) {
                encoded_str.push_back({});
                encoded_str.push_back(split_char);
                continue;
            }

            // iterate characters
            // invert bits and XOR the char byte with key.
            for(auto _char : current_str) {
                encrypted_char = _XOR_with_key(_invert_bits(_char));
                encoded_str.push_back(encrypted_char);
            }

            if(i == strs.size() - 1) { break; } // Dont add seperator at the end.
            encoded_str.push_back(split_char);
        }

        for(size_t i{0}; i < encoded_str.size(); i++) {
            cout << "Encoded byte: " << bitset<8>(encoded_str[i]) << endl;
        }

        return encoded_str;
    }

    vector<string> decode(const string s) {
        vector<string> decoded_vec{};
        decoded_vec.reserve(sizeof(s));
        string str_element{};
        char decoded_char{};

        for(size_t _char{0}; _char < s.length(); _char++) {
            if(s[_char] == '\0') {
                continue;
            }

            if(s[_char] == split_char) {
                decoded_vec.push_back(str_element);
                str_element.clear();
                continue;
            }

            if(_char == s.length() - 1) {
                decoded_char = _invert_bits(_XOR_with_key(s[_char]));
                str_element.push_back(decoded_char);
                decoded_vec.push_back(str_element);
                continue;
            }

            decoded_char = _invert_bits(_XOR_with_key(s[_char]));
            str_element.push_back(decoded_char);
        }

        for(size_t i{0}; i < decoded_vec.size(); i++) {
            for(auto _char : decoded_vec[i]) {
                cout << "Decoded byte: " << bitset<8>(_char) << endl;
            }
        }

        return decoded_vec;
    }

private:
    inline char _invert_bits(char c) { return (~c); }
    inline char _XOR_with_key(char c) { return (c^encryption_key); }

    const uint8_t encryption_key{69};
    const char split_char{'-'};
};

int main() {
    vector<string> msg {
        "hello", "this", "message", "is", "encrypted."
    };

    for(auto word : msg) {
        for(auto _char : word) {
            cout << "Raw Bytes: " << bitset<8>(_char) << endl;
        }
    }

    Codec codec{};
    string encoded_message{codec.encode(msg)};
    cout << "encoded message: " << encoded_message << endl;
    vector<string> decoded_message {codec.decode(encoded_message)};

    for(auto word : decoded_message) {
        for(auto _char : word) {
            cout << _char;
        }
        cout << " ";
    }
    cout << endl;

    if(msg == decoded_message) {
        cout << "Input message matches output message." << endl;
    } else {
        cout << "Error, Message missmatch!" << endl;
    }

    return 0;
}
#ifndef HASHINGUTILITY_H
#define HASHINGUTILITY_H

#include <openssl/sha.h>  // OpenSSL for SHA-256
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdexcept>

namespace HashingUtility {

    // Function to compute SHA-256 hash of a file
    string hashFile(const string& filePath) {
        ifstream file(filePath, ios::binary);
        if (!file) {
            throw runtime_error("Failed to open file: " + filePath);
        }

        SHA256_CTX sha256;
        SHA256_Init(&sha256);
        
        char buffer[8192];
        while (file.read(buffer, sizeof(buffer))) {
            SHA256_Update(&sha256, buffer, file.gcount());
        }
        // Process the last portion of the file
        SHA256_Update(&sha256, buffer, file.gcount());

        // Finalize the hash
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256_Final(hash, &sha256);

        // Convert the hash to a hex string
        stringstream ss;
        for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
            ss << hex << setw(2) << setfill('0') << (int)hash[i];
        }

        return ss.str();
    }

} // namespace HashingUtility


#endif // HASHINGUTILITY_H
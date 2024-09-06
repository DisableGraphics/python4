#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <openssl/sha.h>
#include <vector>
#include <cpuid.h>
#include <regex>

class Python4Interpreter {
public:
    Python4Interpreter(const std::string& script) {
        this->script = script;
        std::srand(std::time(nullptr));
    }

    void run() {
		std::ifstream file(script);
        checkHardwareSHA512(file);
        allocateMemory();
        parseScript(file);
    }

private:
    std::string script;

    void checkHardwareSHA512(std::ifstream &file) {
		unsigned int sig;
		uint64_t val = uint64_t(__get_cpuid_max(0, &sig)) << 32;
		val |= sig;
        std::string hardwareID = std::to_string(val);
		std::cout << "HWID: " << hardwareID << std::endl;
        unsigned char hash[SHA512_DIGEST_LENGTH];
        SHA512((unsigned char*)hardwareID.c_str(), hardwareID.size(), hash);

        std::string embeddedHash = getEmbeddedHash(file);
        std::string calculatedHash = hashToString(hash);

        if (embeddedHash != calculatedHash) {
            throw std::runtime_error("Hardware mismatch. Script cannot be run. " + embeddedHash + " != " + calculatedHash);
        }
    }

	std::string trim(const std::string& str) {
		const std::string whitespace = " \t\n\r\f\v";
		std::string s = str;
		s.erase(0, s.find_first_not_of(whitespace));
		s.erase(s.find_last_not_of(whitespace) + 1);
		return s;
	}

    std::string getEmbeddedHash(std::ifstream &file) {
        // Assume the script has the SHA512 hash embedded as the first line
        std::string hashLine;
        std::getline(file, hashLine);
        return hashLine;
    }

    std::string hashToString(unsigned char* hash) {
        std::stringstream ss;
        for (int i = 0; i < SHA512_DIGEST_LENGTH; ++i) {
            ss << std::hex << (int)hash[i];
        }
        return ss.str();
    }

	const static size_t GB = 1024*1024*1024;

    void allocateMemory() {
        char* memoryLeak = (char*)malloc(10*GB); // 10 GB memory leak
        if (!memoryLeak) {
            throw std::runtime_error("Memory allocation failed.");
        }
		for(size_t i = 0; i < 10e9; i++) {
			memoryLeak[i] = 0xFF;
		}
    }

    void parseScript(std::ifstream &file) {
        std::string line;
        while (std::getline(file, line)) {
			if(line == "") continue;
            if (line.find('\t') != std::string::npos) {
                throw std::runtime_error("Tabs are not allowed. Use spaces.");
            }
            if (line.find("from ") != std::string::npos || line.find("import ") != std::string::npos) {
				std::string modname = line.substr(line.find(' ')+1);
                throw std::runtime_error("ModuleNotFoundError: No module named '" + modname + "'");
            }
            executeLine(line);
        }
    }

    void executeLine(const std::string& line) {
        for (int i = 0; i < 1000; ++i) { // Implicit loop to slow things down

        }

        if (line.find('=') != std::string::npos) {
            throwTypeError();
        }

        std::cout << "This python4 process has been blocked by the GIL. Please wait.\n";
    }

    void throwTypeError() {
        std::vector<std::string> errors = {
            "TypeError: Can't convert 'int' object to str implicitly",
            "TypeError: 'NoneType' object is not callable",
            "TypeError: 'float' object cannot be interpreted as an integer",
			"TypeError: 'str' object cannot be interpreted as a function",
			"TypeError: 'int' object is not iterable",
			"TypeError: Cannot compare types 'list' and 'dict'",
			"TypeError: 'tuple' object does not support item assignment",
			"TypeError: 'NoneType' object has no attribute 'assign'",
			"TypeError: 'set' object is not callable",
			"TypeError: 'float' object has no len()",
			"TypeError: 'int' object is not subscriptable",
			"TypeError: 'dict' object cannot be concatenated with 'list'",
			"TypeError: Unsupported operand type(s) for =: 'int' and 'str'",
			"TypeError: 'list' object cannot be multiplied by a non-int of type 'float'",
			"TypeError: 'str' object has no attribute 'pop'",
			"TypeError: Cannot unpack non-iterable 'NoneType' object",
			"TypeError: 'int' object cannot be converted to 'str' implicitly",
			"TypeError: 'range' object does not support item deletion",
			"TypeError: Object of type 'bytes' is not JSON serializable",
			"TypeError: 'complex' object cannot be converted to 'float'",
			"TypeError: a bytes-like object is required, not 'str'",
			"TypeError: 'list' object has no attribute 'values'",
			"TypeError: 'frozenset' object has no attribute 'add'",
			"TypeError: 'generator' object is not subscriptable",
			"TypeError: Missing 1 required positional argument",
			"TypeError: 'NoneType' object cannot be interpreted as an integer",
			"TypeError: Cannot combine 'float' and 'decimal.Decimal'",
			"TypeError: 'str' object is not an iterator",
        };
        int randomIndex = std::rand() % errors.size();
        throw std::runtime_error(errors[randomIndex]);
    }
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: python4 <script.py4>\n";
        return 1;
    }

    try {
        Python4Interpreter interpreter(argv[1]);
        interpreter.run();
    } catch (const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }

    return 0;
}

